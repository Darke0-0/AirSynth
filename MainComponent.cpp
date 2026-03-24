#include "MainComponent.h"

MainComponent::MainComponent()
    : dataInputComponent([this](float x1, float y1, float z1, float x2, float y2, float z2) {
        handleSensorData(x1, y1, z1, x2, y2, z2);
    }) {
    audioEngine.start();
}

MainComponent::~MainComponent() {
    audioEngine.stop();
}

void MainComponent::handleSensorData(float x1, float y1, float z1, float x2, float y2, float z2) {
    float minFreq = 100.0f;
    float maxFreq = 2000.0f;
    
    float freq = minFreq + (maxFreq - minFreq) * ((x1 + 1.0f) / 2.0f);
    float amp = (y1 + 1.0f) / 2.0f;
    float modDepth = z1;

    float filterCutoff = 500.0f + (x2 * 2000.0f);
    float reverbAmount = (y2 + 1.0f) / 2.0f;
    float fmIntensity = z2 * 10.0f;

    audioEngine.clearOscillators();
    audioEngine.addOscillator(freq, amp, modDepth);
    audioEngine.setFilterCutoff(filterCutoff);
    audioEngine.setReverbAmount(reverbAmount);
    audioEngine.setFMIntensity(fmIntensity);
}

void MainComponent::run() {
    dataInputComponent.run();
}
