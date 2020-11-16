#pragma once

#include <fake-jni/fake-jni.h>

struct AudioDeviceInternal;

class AudioDevice : public FakeJni::JObject {

    std::shared_ptr<AudioDeviceInternal> dev = nullptr;

public:
    DEFINE_CLASS_NAME("org/fmod/AudioDevice")

    AudioDevice();

    FakeJni::JBoolean init(FakeJni::JInt channels, FakeJni::JInt samplerate, FakeJni::JInt c, FakeJni::JInt d);

    void write(std::shared_ptr<FakeJni::JByteArray> data, FakeJni::JInt length);

    void close();
};