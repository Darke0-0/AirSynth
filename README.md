# Air Synth

A **gesture-based music synthesizer** that empowers users to create real-time audio and music using physical movements. It utilizes sensor data and intuitive hardware interactions to drive powerful sound synthesis.

Checkout the [Official Website](https://darke0-0.github.io/AirSynth/) for more details and demonstrations!

## 🌟 Key Features

* **Real-Time Audio Synthesis:** Utilizes `RtAudio` and `STK` (Synthesis ToolKit) for low-latency, dynamic sound generation.
* **Gesture Recognition & Motion Control:** Reads motion data via an MPU6050 IMU sensor (I2C) to control musical parameters seamlessly.
* **Interactive UI & Event Handling:** Driven by `SDL2` for data input mapping and user interfacing.
* **Embedded Hardware Integration:** Designed to run on a Raspberry Pi using `libgpiod` for direct GPIO button and sensor communication.
* **Custom Audio Engine:** Contains customizable modular components for oscillators, filter cutoffs, reverb, and FM synthesis intensity.

## 🛠️ System Architecture

Air Synth is built using a modern C++17 modular architecture:
* **Audio Engine (`AudioEngine`)**: Manages real-time audio contexts, oscillators, DSP filters, and effects routing.
* **Data Input Component (`DataInputComponent`)**: Handles SDL2-driven visual sliders and normalizes mapped input values from the hardware.
* **IMU & Sensor Drivers (`IMU`, `Button`)**: Interprets GPIO signals and I2C telemetry (via MPU6050) directly from the Raspberry Pi.

## 📦 Prerequisites

Ensure you have the following dependencies installed on your system (specifically targeted for Raspberry Pi / Linux environments):

* **CMake** (v3.25 or higher)
* **C++17 Compatible Compiler** (GCC/Clang)
* **RtAudio** (`librtaudio-dev`)
* **STK** (`libstk0-dev`)
* **SDL2** (`libsdl2-dev`)
* **libgpiod** (`libgpiod-dev`)

## 🚀 Build Instructions

1. Clone the repository and navigate to the project repository.
2. Ensure you are in the `AirSynth` directory, and run the following command to generate the build files:
    ```bash
    cmake -G "Unix Makefiles" -B build
    ```
    *(Note: This uses the **Unix Makefiles** generator for compiling in the `build` folder. If you prefer the default generator, run: `cmake -B build`)*

3. Compile the project:
    ```bash
    cmake --build ./build --config Release --target AirSynth
    ```

## 🎮 Running the Code

> **Important:** The sensors (MPU6050) and physical buttons **must** be connected to the Raspberry Pi's GPIO pins before launching the executable.

Please see the [Hardware Section on the Wiki](https://github.com/Darke0-0/AirSynth/wiki#hardware) for the complete circuit diagram and pinout instructions.

Once built and hardware is connected, launch the synthesizer:
```bash
./build/AirSynth
```
Exit the program gracefully using `Ctrl+C`, which triggers the internal shutdown sequence to safely close audio contexts and UI threads.
