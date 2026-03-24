#pragma once

#include <rtaudio/RtAudio.h>
#include <vector>
#include <atomic>

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    void start();
    void stop();
    void addOscillator(float freq, float amp, float modDepth);
    void setFilterCutoff(float value);
    void setReverbAmount(float value);
    void setFMIntensity(float value);
    void clearOscillators();

private:
    static int audioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void* userData);
    
    RtAudio dac;
    std::vector<float> oscillators;
    std::atomic<float> filterCutoff{1000.0f}, reverbAmount{0.5f}, fmIntensity{0.0f};
};
