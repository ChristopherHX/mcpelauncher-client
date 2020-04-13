#include "window_callbacks.h"
#include "symbols.h"

#include <mcpelauncher/minecraft_version.h>
#include <game_window_manager.h>
#include <log.h>
#include <mcpelauncher/path_helper.h>

WindowCallbacks::WindowCallbacks(GameWindow &window, JniSupport &jniSupport, FakeInputQueue &inputQueue) :
    window(window), jniSupport(jniSupport), inputQueue(inputQueue) {
    useDirectMouseInput = true;
    useDirectKeyboardInput = (Keyboard::_states && Keyboard::_inputs && Keyboard::_gameControllerId);
}

void WindowCallbacks::registerCallbacks() {
    using namespace std::placeholders;
    window.setWindowSizeCallback(std::bind(&WindowCallbacks::onWindowSizeCallback, this, _1, _2));
    window.setCloseCallback(std::bind(&WindowCallbacks::onClose, this));

    window.setMouseButtonCallback(std::bind(&WindowCallbacks::onMouseButton, this, _1, _2, _3, _4));
    window.setMousePositionCallback(std::bind(&WindowCallbacks::onMousePosition, this, _1, _2));
    window.setMouseRelativePositionCallback(std::bind(&WindowCallbacks::onMouseRelativePosition, this, _1, _2));
    window.setMouseScrollCallback(std::bind(&WindowCallbacks::onMouseScroll, this, _1, _2, _3, _4));
    window.setTouchStartCallback(std::bind(&WindowCallbacks::onTouchStart, this, _1, _2, _3));
    window.setTouchUpdateCallback(std::bind(&WindowCallbacks::onTouchUpdate, this, _1, _2, _3));
    window.setTouchEndCallback(std::bind(&WindowCallbacks::onTouchEnd, this, _1, _2, _3));
    window.setKeyboardCallback(std::bind(&WindowCallbacks::onKeyboard, this, _1, _2));
    window.setKeyboardTextCallback(std::bind(&WindowCallbacks::onKeyboardText, this, _1));
    window.setPasteCallback(std::bind(&WindowCallbacks::onPaste, this, _1));
    window.setGamepadStateCallback(std::bind(&WindowCallbacks::onGamepadState, this, _1, _2));
    window.setGamepadButtonCallback(std::bind(&WindowCallbacks::onGamepadButton, this, _1, _2, _3));
    window.setGamepadAxisCallback(std::bind(&WindowCallbacks::onGamepadAxis, this, _1, _2, _3));
}

void WindowCallbacks::onWindowSizeCallback(int w, int h) {
    jniSupport.onWindowResized(w, h);
}

void WindowCallbacks::onClose() {
    jniSupport.onWindowClosed();
}

void WindowCallbacks::onMouseButton(double x, double y, int btn, MouseButtonAction action) {
    if (btn < 1 || btn > 3)
        return;
    if (useDirectMouseInput)
        Mouse::feed((char) btn, (char) (action == MouseButtonAction::PRESS ? 1 : 0), (short) x, (short) y, 0, 0);
    else if (action == MouseButtonAction::PRESS)
        inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_DOWN, 0, x, y));
    else if (action == MouseButtonAction::RELEASE)
        inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_UP, 0, x, y));
}
void WindowCallbacks::onMousePosition(double x, double y) {
    if (useDirectMouseInput)
        Mouse::feed(0, 0, (short) x, (short) y, 0, 0);
    else
        inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_MOVE, 0, x, y));
}
void WindowCallbacks::onMouseRelativePosition(double x, double y) {
    if (useDirectMouseInput)
        Mouse::feed(0, 0, 0, 0, (short) x, (short) y);
    else
        inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_MOVE, 0, x, y));
}
void WindowCallbacks::onMouseScroll(double x, double y, double dx, double dy) {
    char cdy = (char) std::max(std::min(dy * 127.0, 127.0), -127.0);
    if (useDirectMouseInput)
        Mouse::feed(4, cdy, 0, 0, (short) x, (short) y);
}
void WindowCallbacks::onTouchStart(int id, double x, double y) {
    inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_DOWN, id, x, y));
}
void WindowCallbacks::onTouchUpdate(int id, double x, double y) {
    inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_MOVE, id, x, y));
}
void WindowCallbacks::onTouchEnd(int id, double x, double y) {
    inputQueue.addEvent(FakeMotionEvent(AMOTION_EVENT_ACTION_UP, id, x, y));
}
void WindowCallbacks::onKeyboard(mapping::KeyCode key, KeyAction action) {
#ifdef __APPLE__
    if (key == mapping::KeyCode::LEFT_SUPER || key == mapping::KeyCode::RIGHT_SUPER)
#else
    if (key == mapping::KeyCode::LEFT_CTRL || key == mapping::KeyCode::RIGHT_CTRL)
#endif
        modCTRL = (action != KeyAction::RELEASE);

    if (modCTRL && key == mapping::KeyCode::C) {
        window.setClipboardText(jniSupport.getTextInputHandler().getCopyText());
    } else {
        jniSupport.getTextInputHandler().onKeyPressed(key, action);
    }

    if (useDirectKeyboardInput && (action == KeyAction::PRESS || action == KeyAction::RELEASE)) {
        Keyboard::InputEvent evData {};
        evData.key = (unsigned int) key;
        evData.event = (action == KeyAction::PRESS ? 1 : 0);
        evData.controllerId = *Keyboard::_gameControllerId;
        Keyboard::_inputs->push_back(evData);
        Keyboard::_states[(int) key] = evData.event;
        return;
    }

    if (action == KeyAction::PRESS)
        inputQueue.addEvent(FakeKeyEvent(AKEY_EVENT_ACTION_DOWN, mapMinecraftToAndroidKey(key)));
    else if (action == KeyAction::RELEASE)
        inputQueue.addEvent(FakeKeyEvent(AKEY_EVENT_ACTION_UP, mapMinecraftToAndroidKey(key)));

}
void WindowCallbacks::onKeyboardText(std::string const& c) {
    if (c == "\n" && !jniSupport.getTextInputHandler().isMultiline())
        jniSupport.onReturnKeyPressed();
    else
        jniSupport.getTextInputHandler().onTextInput(c);
}
void WindowCallbacks::onPaste(std::string const& str) {
    jniSupport.getTextInputHandler().onTextInput(str);
}
void WindowCallbacks::onGamepadState(int gamepad, bool connected) {
    Log::trace("WindowCallbacks", "Gamepad %s #%i", connected ? "connected" : "disconnected", gamepad);
    if (connected)
        gamepads.insert({gamepad, GamepadData()});
    else
        gamepads.erase(gamepad);
    jniSupport.setGameControllerConnected(gamepad, connected);
}

void WindowCallbacks::onGamepadButton(int gamepad, GamepadButtonId btn, bool pressed) {
    if (pressed)
        inputQueue.addEvent(FakeKeyEvent(AINPUT_SOURCE_GAMEPAD, gamepad, AKEY_EVENT_ACTION_DOWN, mapGamepadToAndroidKey(btn)));
    else
        inputQueue.addEvent(FakeKeyEvent(AINPUT_SOURCE_GAMEPAD, gamepad, AKEY_EVENT_ACTION_UP, mapGamepadToAndroidKey(btn)));
}

void WindowCallbacks::onGamepadAxis(int gamepad, GamepadAxisId ax, float value) {
    auto gpi = gamepads.find(gamepad);
    if (gpi == gamepads.end())
        return;
    auto& gp = gpi->second;
    if ((int) ax < 0 || (int) ax >= 6)
        throw std::runtime_error("bad axis id");
    gp.axis[(int) ax] = value;

    if (needsQueueGamepadInput) {
        inputQueue.addEvent(FakeMotionEvent(AINPUT_SOURCE_GAMEPAD, gamepad, AMOTION_EVENT_ACTION_MOVE, 0, 0.f, 0.f,
                [this, gamepad](int axis) {
                    auto gpi = gamepads.find(gamepad);
                    if (gpi == gamepads.end())
                        return 0.f;
                    auto& gp = gpi->second;
                    if (axis == AMOTION_EVENT_AXIS_X) return gp.axis[(int) GamepadAxisId::LEFT_X];
                    if (axis == AMOTION_EVENT_AXIS_Y) return gp.axis[(int) GamepadAxisId::LEFT_Y];
                    if (axis == AMOTION_EVENT_AXIS_RX) return gp.axis[(int) GamepadAxisId::RIGHT_X];
                    if (axis == AMOTION_EVENT_AXIS_RY) return gp.axis[(int) GamepadAxisId::RIGHT_Y];
                    if (axis == AMOTION_EVENT_AXIS_LTRIGGER) return gp.axis[(int) GamepadAxisId::LEFT_TRIGGER];
                    if (axis == AMOTION_EVENT_AXIS_RTRIGGER) return gp.axis[(int) GamepadAxisId::RIGHT_TRIGGER];
                    return 0.f;
                }));
        needsQueueGamepadInput = false;
    }
}

void WindowCallbacks::loadGamepadMappings() {
    auto windowManager = GameWindowManager::getManager();
    std::vector<std::string> controllerDbPaths;
    PathHelper::findAllDataFiles("gamecontrollerdb.txt", [&controllerDbPaths](std::string const &path) {
        controllerDbPaths.push_back(path);
    });
    for (std::string const& path : controllerDbPaths) {
        Log::trace("Launcher", "Loading gamepad mappings: %s", path.c_str());
        windowManager->addGamepadMappingFile(path);
    }
}

WindowCallbacks::GamepadData::GamepadData() {
    for (int i = 0; i < 6; i++)
        axis[i] = 0.f;
}

int WindowCallbacks::mapMinecraftToAndroidKey(mapping::KeyCode code) {
    if (code >= mapping::KeyCode::NUM_0 && code <= mapping::KeyCode::NUM_9)
        return (int) code - (int) mapping::KeyCode::NUM_0 + AKEYCODE_0;
    if (code >= mapping::KeyCode::A && code <= mapping::KeyCode::Z)
        return (int) code - (int) mapping::KeyCode::A + AKEYCODE_A;
    if (code >= mapping::KeyCode::FN1 && code <= mapping::KeyCode::FN12)
        return (int) code - (int) mapping::KeyCode::FN1 + AKEYCODE_F1;
    switch (code) {
        case mapping::KeyCode::BACK: return AKEYCODE_BACK;
        case mapping::KeyCode::BACKSPACE: return AKEYCODE_DEL;
        case mapping::KeyCode::TAB: return AKEYCODE_TAB;
        case mapping::KeyCode::ENTER: return AKEYCODE_ENTER;
        case mapping::KeyCode::LEFT_SHIFT: return AKEYCODE_SHIFT_LEFT;
        case mapping::KeyCode::RIGHT_SHIFT: return AKEYCODE_SHIFT_RIGHT;
        case mapping::KeyCode::LEFT_CTRL: return AKEYCODE_CTRL_LEFT;
        case mapping::KeyCode::RIGHT_CTRL: return AKEYCODE_CTRL_RIGHT;
        case mapping::KeyCode::PAUSE: return AKEYCODE_BREAK;
        case mapping::KeyCode::CAPS_LOCK: return AKEYCODE_CAPS_LOCK;
        case mapping::KeyCode::ESCAPE: return AKEYCODE_ESCAPE;
        case mapping::KeyCode::SPACE: return AKEYCODE_SPACE;
        case mapping::KeyCode::PAGE_UP: return AKEYCODE_PAGE_UP;
        case mapping::KeyCode::PAGE_DOWN: return AKEYCODE_PAGE_DOWN;
        case mapping::KeyCode::END: return AKEYCODE_MOVE_END;
        case mapping::KeyCode::HOME: return AKEYCODE_MOVE_HOME;
        case mapping::KeyCode::LEFT: return AKEYCODE_DPAD_LEFT;
        case mapping::KeyCode::UP: return AKEYCODE_DPAD_UP;
        case mapping::KeyCode::RIGHT: return AKEYCODE_DPAD_RIGHT;
        case mapping::KeyCode::DOWN: return AKEYCODE_DPAD_DOWN;
        case mapping::KeyCode::INSERT: return AKEYCODE_INSERT;
        case mapping::KeyCode::DELETE: return AKEYCODE_FORWARD_DEL;
        case mapping::KeyCode::NUM_LOCK: return AKEYCODE_NUM_LOCK;
        case mapping::KeyCode::SCROLL_LOCK: return AKEYCODE_SCROLL_LOCK;
        case mapping::KeyCode::SEMICOLON: return AKEYCODE_SEMICOLON;
        case mapping::KeyCode::EQUAL: return AKEYCODE_EQUALS;
        case mapping::KeyCode::COMMA: return AKEYCODE_COMMA;
        case mapping::KeyCode::MINUS: return AKEYCODE_MINUS;
        case mapping::KeyCode::PERIOD: return AKEYCODE_PERIOD;
        case mapping::KeyCode::SLASH: return AKEYCODE_SLASH;
        case mapping::KeyCode::GRAVE: return AKEYCODE_GRAVE;
        case mapping::KeyCode::LEFT_BRACKET: return AKEYCODE_LEFT_BRACKET;
        case mapping::KeyCode::BACKSLASH: return AKEYCODE_BACKSLASH;
        case mapping::KeyCode::RIGHT_BRACKET: return AKEYCODE_RIGHT_BRACKET;
        case mapping::KeyCode::APOSTROPHE: return AKEYCODE_APOSTROPHE;
        case mapping::KeyCode::MENU: return AKEYCODE_MENU;
        case mapping::KeyCode::LEFT_SUPER: return AKEYCODE_META_LEFT;
        case mapping::KeyCode::RIGHT_SUPER: return AKEYCODE_META_RIGHT;
        case mapping::KeyCode::LEFT_ALT: return AKEYCODE_ALT_LEFT;
        case mapping::KeyCode::RIGHT_ALT: return AKEYCODE_ALT_RIGHT;
        default: return AKEYCODE_UNKNOWN;
    }
}

int WindowCallbacks::mapGamepadToAndroidKey(GamepadButtonId btn) {
    switch (btn) {
        case GamepadButtonId::A: return AKEYCODE_BUTTON_A;
        case GamepadButtonId::B: return AKEYCODE_BUTTON_B;
        case GamepadButtonId::X: return AKEYCODE_BUTTON_X;
        case GamepadButtonId::Y: return AKEYCODE_BUTTON_Y;
        case GamepadButtonId::LB: return AKEYCODE_BUTTON_L1;
        case GamepadButtonId::RB: return AKEYCODE_BUTTON_R1;
        case GamepadButtonId::BACK: return AKEYCODE_BUTTON_SELECT;
        case GamepadButtonId::START: return AKEYCODE_BUTTON_START;
        case GamepadButtonId::GUIDE: return AKEYCODE_BUTTON_MODE;
        case GamepadButtonId::LEFT_STICK: return AKEYCODE_BUTTON_THUMBL;
        case GamepadButtonId::RIGHT_STICK: return AKEYCODE_BUTTON_THUMBR;
        case GamepadButtonId::DPAD_UP: return AKEYCODE_DPAD_UP;
        case GamepadButtonId::DPAD_RIGHT: return AKEYCODE_DPAD_RIGHT;
        case GamepadButtonId::DPAD_DOWN: return AKEYCODE_DPAD_DOWN;
        case GamepadButtonId::DPAD_LEFT: return AKEYCODE_DPAD_LEFT;
        default: return -1;
    }
}