#include <queue>
#include <mutex>
#include <game_window_manager.h>

class InputQueue {
public:
    static InputQueue * instance;

    struct KeyEvent {
        int key;
        KeyAction action;
        int repeat;
        int metastate;
    };
    std::mutex guard;
    int metastate;
    std::queue<KeyEvent> queue;
};