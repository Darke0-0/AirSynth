#pragma once

#include "AudioEngine.h"
#include "DataInputComponent.h"

class MainComponent {
public:
    MainComponent();
    ~MainComponent();
    void run();

private:
    void handleSensorData(float x1, float y1, float z1, float x2, float y2, float z2);

    AudioEngine audioEngine;
    DataInputComponent dataInputComponent;
};
