#include <SDL2/SDL.h>
#include <rtaudio/RtAudio.h>
#include <iostream>
#include <csignal>
#include <atomic>
#include <condition_variable>
#include "MainComponent.h"

std::atomic<bool> keepRunning{true};

std::mutex mtx;
std::condition_variable cv;

void signalHandler(int signum) {
    std::cout << "\n[INFO] Interrupt signal (" << signum << ") received. Stopping AirSynth..." << std::endl;
    keepRunning = false;
    cv.notify_all();
}

// ✅ Make sure SDL2 recognizes main function properly
int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);  // Handle Ctrl+C interrupt

    std::cout << "[INFO] Initializing AirSynth..." << std::endl;
    
    // Initialize the main component (UI & Audio Engine)
    MainComponent mainComponent;
    mainComponent.run();  // Start the main loop

    // Keep running until an external event (e.g., Ctrl+C) stops it
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return !keepRunning; });

    std::cout << "[INFO] AirSynth Stopped." << std::endl;
    return 0;
}
