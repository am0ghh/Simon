# Simon Says Embedded System Shield

A memory-sequencing game built as a custom Arduino Uno R3 expansion shield, laid out in KiCad.

## Project Overview

The classic "Simon Says" game on a purpose-built 2-layer PCB. The Arduino plays back a growing random sequence on four colored LEDs with a matching tone per color, then reads the player's attempt back through four tactile buttons. Each correct round appends another step.

The interesting part of this project is the board, not the firmware — see *Hardware Design* below.

## Features

* **Custom PCB shield** — 2-layer FR4, designed in KiCad 9.0.7, with header spacing matched to the Uno R3 form factor so it seats directly on the board.
* **Dedicated ground pour** — GND poured on `B.Cu` to keep return paths short.
* **Per-channel layout blocks** — each button/LED/resistor group laid out as its own signal block, which keeps traces short and the board symmetric.
* **Audio-visual feedback** — four LEDs with matched tones (880 / 932 / 1046 / 1174 Hz) driven by `tone()` on a piezo buzzer.
* **Seeded randomness** — `randomSeed(analogRead(0))` on a floating analog pin, so the sequence differs between power cycles.

## Components

* **Microcontroller:** Arduino Uno R3
* **Custom PCB:** Simon Says Shield (2-layer FR4)
* **Buttons:** 4× 6 mm tactile switches
* **LEDs:** 4× 5 mm (red, green, blue, yellow)
* **Resistors:** 4× 220 Ω (LEDs), 1× 100 Ω (buzzer)
* **Buzzer:** 1× piezo
* **Connectors:** 1× set of male pin headers

## Pin Connections

| Channel | LED pin | Button pin | Tone |
|---|---|---|---|
| Green  | 8  | 3 (internal pull-up) | 880 Hz  |
| Blue   | 9  | 4 (internal pull-up) | 932 Hz  |
| Yellow | 10 | 5 (internal pull-up) | 1046 Hz |
| Red    | 11 | 2 (internal pull-up) | 1174 Hz |

**Buzzer:** pin 6.

Buttons are wired active-low against `INPUT_PULLUP`.

## How It Works

1. A new random step (1–4) is appended to the sequence vector each round.
2. The full sequence plays back — LED on, tone on, 200 ms, off, 50 ms gap.
3. The firmware then waits for each button press in order, lighting the pressed color and sounding its tone while held.
4. A wrong press triggers a 150 Hz game-over tone, flashes all four LEDs, clears the sequence, and restarts.

## Firmware Limitations

Stated plainly, because the code is short enough that anyone reading it will notice:

* **The main loop is blocking.** Playback and feedback use `delay()`, and `getButtonPressed()` is a busy-wait spin loop. The firmware is not a state machine — there is no state variable and no non-blocking scheduler.
* **There is no debouncing.** Button release is handled by spinning until the pin returns high (`while (digitalRead(pin) == LOW);`), which happens to mask contact bounce in practice but is not debouncing and does nothing about bounce on the press edge.
* **Input has no timeout.** The game waits indefinitely for a press.

Rewriting this as a genuine non-blocking FSM with `millis()`-based timing and real debouncing is the obvious next step, and the board supports it without changes.

## Installation

1. Open the project in **KiCad 9.0.7** to view the schematic and PCB layout.
2. Upload `main.cpp` using **PlatformIO** or the Arduino IDE.
3. Solder components starting with the resistors, then the taller parts — buttons, buzzer, headers.
4. Seat the shield on the Arduino Uno R3.

## Usage

* Power the Arduino over USB or a 9 V barrel jack.
* Watch the sequence, then replicate it with the buttons.
* Each successful round adds one more step.

## Future Improvements

* Rewrite the firmware as a non-blocking FSM with real debouncing.
* EEPROM persistence for high scores.
* AVR sleep modes while idle.
* A shrinking input-timing window as the sequence grows.

## License

MIT License
