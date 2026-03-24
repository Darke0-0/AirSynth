#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <atomic>

class DataInputComponent {
public:
    explicit DataInputComponent(std::function<void(float, float, float, float, float, float)> callback);
    ~DataInputComponent();
    
    void run();
    void stop();

private:
    void handleEvent(SDL_Event& event);
    float mapSliderValue(int value, int min, int max, float rangeMin, float rangeMax);
    void renderUI();

    std::function<void(float, float, float, float, float, float)> dataCallback;
    std::atomic<bool> running{true};

    SDL_Window* window{nullptr};
    SDL_Renderer* renderer{nullptr};

    SDL_Rect sliders[6], indicators[6];
    float values[6]{0.0f};
};
