#include "AudioEngine.h"
#include <iostream>
#include <cmath>

AudioEngine::AudioEngine() {
    if (dac.getDeviceCount() < 1) {
        std::cerr << "[ERROR] No audio devices found!" << std::endl;
        exit(1);
    }
}

AudioEngine::~AudioEngine() {
    stop();
}

void AudioEngine::start() {
    RtAudio::StreamParameters params;
    params.deviceId = dac.getDefaultOutputDevice();
    params.nChannels = 1;
    params.firstChannel = 0;
    unsigned int bufferFrames = 256;

    try {
        dac.openStream(&params, nullptr, RTAUDIO_FLOAT32, 44100, &bufferFrames, &audioCallback, this);
        dac.startStream();
    } catch (std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        stop();
    }
}

void AudioEngine::stop() {
    if (dac.isStreamOpen()) {
        dac.stopStream();
        dac.closeStream();
    }
}

void AudioEngine::addOscillator(float freq, float amp, float modDepth) {
    oscillators.push_back(freq);
}

void AudioEngine::setFilterCutoff(float value) {
    filterCutoff.store(value);
}

void AudioEngine::setReverbAmount(float value) {
    reverbAmount.store(value);
}

void AudioEngine::setFMIntensity(float value) {
    fmIntensity.store(value);
}

void AudioEngine::clearOscillators() {
    oscillators.clear();
}

int AudioEngine::audioCallback(void* outputBuffer, void*, unsigned int nBufferFrames, double, RtAudioStreamStatus status, void* userData) {
    AudioEngine* engine = static_cast<AudioEngine*>(userData);
    float* buffer = static_cast<float*>(outputBuffer);
    for (unsigned int i = 0; i < nBufferFrames; i++) {
        buffer[i] = 0.0f;
        for (auto& freq : engine->oscillators) {
            buffer[i] += std::sin(2.0 * M_PI * freq * i / 44100);
        }
        buffer[i] /= engine->oscillators.size();
    }
    return 0;
}
