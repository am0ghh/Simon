# Simon Says Embedded System Shield
An engineering-grade memory-sequencing game designed as an Arduino Uno R3 expansion shield, utilizing Synchronous State Logic and Finite State Machine (FSM) architecture.

## Project Overview
This project transitions the classic "Simon Says" game into a robust embedded environment. By moving away from blocking `delay()` functions and adopting a non-blocking FSM, the system achieves deterministic timing and responsive tactile polling.

## Features
* **Synchronous Finite State Machine** - Deterministic state transitions for game logic, playback, and input handling.
* **Tactile Interface** - 4x push buttons with software-based debouncing to eliminate mechanical contact noise.
* **Audio-Visual Feedback** - Synchronized high-brightness LEDs and PWM-driven piezo buzzer for multi-modal cues.
* **Integrated Ground Plane** - 2-layer PCB design with a dedicated GND pour on B.Cu to minimize EMI and signal return loops.
* **Dynamic Entropy** - Pseudo-random sequence generation using noise harvested from floating analog pins.

## Components Required
* **Microcontroller**: Arduino Uno R3
* **Custom PCB**: Simon Says Shield (2-Layer FR4)
* **Buttons**: 4x 6mm Tactile Switches
* **LEDs**: 4x 5mm LEDs (Red, Green, Blue, Yellow)
* **Resistors**: 4x 220Ω (LEDs), 1x 100Ω (Buzzer)
* **Buzzer**: 1x Active or Passive Piezo Buzzer
* **Connectors**: 1x Set of Male Pin Headers

## Pin Connections
### User Interface (Input/Output)
* **Red Channel**: LED: Pin 6 | Button: Pin 2 (Internal Pull-up)
* **Green Channel**: LED: Pin 7 | Button: Pin 3 (Internal Pull-up)
* **Blue Channel**: LED: Pin 8 | Button: Pin 4 (Internal Pull-up)
* **Yellow Channel**: LED: Pin 9 | Button: Pin 5 (Internal Pull-up)

### Audio Output
* **Buzzer**: Pin 10 (PWM enabled for frequency-specific tone generation)

## How It Works
1. **Initial State (IDLE)**: The system polls all buttons. A "Press to Start" interrupt-style check initiates the game.
2. **Sequence Generation**: The FSM appends a new step to the array using `random()`. The sequence is stored in a dynamic buffer.
3. **Playback Logic**: The controller iterates through the array, driving the specific LED and PWM frequency for the mapped duration.
4. **Input Polling (Active-Low)**: The system enters a listening state with a timeout. It compares button presses against the stored sequence index.
5. **State Transition (Match/Mismatch)**:
    * **Match**: FSM returns to the Generation state to increment difficulty.
    * **Mismatch**: FSM transitions to the Game Over state, triggering a descending frequency sweep and resetting the score.

## Installation
1. Open the project in **KiCad 9.0.7** to view PCB layouts.
2. Upload the provided FSM-based firmware using **PlatformIO** or Arduino IDE.
3. Solder components to the custom PCB, starting with resistors and moving to taller components like buttons and headers.
4. Mount the shield onto the Arduino Uno R3.

## Usage
* Power the Arduino via USB or a 9V DC barrel jack.
* Watch the initial sequence and replicate it using the buttons.
* The game speed increases as you progress through higher state counts.

## Future Improvements
* **EEPROM Persistence**: Save high scores to non-volatile memory.
* **Advanced Power Management**: Implement AVR sleep modes during IDLE_STATE to conserve power.
* **Difficulty Scaling**: Implement a variable "window" for input timing that decreases as the sequence length increases.

## License
MIT License
