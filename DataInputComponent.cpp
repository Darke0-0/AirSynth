#include "DataInputComponent.h"

DataInputComponent::DataInputComponent(std::function<void(float, float, float, float, float, float)> callback)
    : dataCallback(callback) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("AirSynth Control", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

DataInputComponent::~DataInputComponent() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DataInputComponent::run() {
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) handleEvent(event);
        renderUI();
        SDL_Delay(16);
    }
}

void DataInputComponent::stop() {
    running = false;
}

void DataInputComponent::handleEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON_LMASK)) {
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;
        int index = (mouseY - 50) / 50;
        if (index >= 0 && index < 6) {
            values[index] = mapSliderValue(mouseX, 50, 350, -1.0f, 1.0f);
            dataCallback(values[0], values[1], values[2], values[3], values[4], values[5]);
        }
    }
}

float DataInputComponent::mapSliderValue(int value, int min, int max, float rangeMin, float rangeMax) {
    return rangeMin + ((value - min) * (rangeMax - rangeMin) / (max - min));
}

void DataInputComponent::renderUI() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 6; i++) SDL_RenderFillRect(renderer, &sliders[i]);
    SDL_RenderPresent(renderer);
}
