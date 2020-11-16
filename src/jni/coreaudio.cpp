#include "coreaudio.h"
#include <AudioToolbox/AudioQueue.h>
#include <CoreAudio/CoreAudioTypes.h>
#include <CoreFoundation/CFRunLoop.h>
#include <atomic>

struct AudioDeviceInternal {
    AudioQueueRef queue;
    AudioQueueBufferRef buffers[3];
    std::atomic<int> i;
};

#include <iostream>
static void callback(void *custom_data, AudioQueueRef queue, AudioQueueBufferRef buffer) {
    //std::cerr << "Audio buffer become free\n";
}

AudioDevice::AudioDevice() {

}

FakeJni::JBoolean AudioDevice::init(FakeJni::JInt channels, FakeJni::JInt samplerate, FakeJni::JInt c, FakeJni::JInt d) {
    if (dev != nullptr) {
        throw std::runtime_error("Illegal State, coreaudio already initialized");
    }
    dev = std::make_shared<AudioDeviceInternal>();
    dev->i = 0;

    int bufferByteSize = c * d * channels;

    AudioStreamBasicDescription streamFormat;
    streamFormat.mSampleRate = samplerate;
    streamFormat.mFormatID = kAudioFormatLinearPCM;
    streamFormat.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    streamFormat.mBitsPerChannel = 16;
    streamFormat.mChannelsPerFrame = channels;
    streamFormat.mBytesPerPacket = 2 * streamFormat.mChannelsPerFrame;
    streamFormat.mBytesPerFrame = 2 * streamFormat.mChannelsPerFrame;
    streamFormat.mFramesPerPacket = 1;
    streamFormat.mReserved = 0;

    auto err = AudioQueueNewOutput (&streamFormat, callback, nil, nil, nil, 0, &dev->queue);
    if (err != noErr) {
        throw std::runtime_error("Failed NewOutput " + std::to_string(err));
        return false;
    }
std::cerr << "bufferByteSize:" << bufferByteSize << "\n";
    for (int i = 0; i < 2; i++) {
        err = AudioQueueAllocateBuffer (dev->queue, bufferByteSize, &dev->buffers[i]); 
        if (err != noErr) {
            throw std::runtime_error("Failed allocate buffer " + std::to_string(err));
            return false;
        }
        dev->buffers[i]->mAudioDataByteSize = bufferByteSize;
        err = AudioQueueEnqueueBuffer(dev->queue, dev->buffers[i], 0, NULL);
        if (err != noErr) {
            throw std::runtime_error("Failed enqueue " + std::to_string(err));
        }
    }

    err = AudioQueueStart(dev->queue, nil);
    if (err != noErr) {
        throw std::runtime_error("Failed start queue " + std::to_string(err));
        return false;
    }
    return true;
}

void AudioDevice::write(std::shared_ptr<FakeJni::JByteArray> data, FakeJni::JInt length) {
    // auto buf = dev->buffers[dev->i++ & 1];
    // memcpy(buf->mAudioData, (void*)data->getArray(), length);
    // buf->mAudioDataByteSize = length;
    // OSStatus err = AudioQueueEnqueueBuffer(dev->queue, buf, 0, NULL);
    // if (err != noErr) {
    //     throw std::runtime_error("Failed enqueue " + std::to_string(err));
    // }
    AudioQueueBufferRef buf;
    AudioQueueAllocateBuffer (dev->queue, length, &buf);
    memcpy(buf->mAudioData, (void*)data->getArray(), length);
    buf->mAudioDataByteSize = length;
    OSStatus err = AudioQueueEnqueueBuffer(dev->queue, buf, 0, NULL);
    if (err != noErr) {
        throw std::runtime_error("Failed enqueue " + std::to_string(err));
    }
}

void AudioDevice::close() {
    auto err = AudioQueueStop(dev->queue, true);
    if (err != noErr) {
        throw std::runtime_error("Failed stop " + std::to_string(err));

        return;
    }
}