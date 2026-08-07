# Multifunction Button Library

A robust, non-blocking Arduino library designed to handle hardware buttons efficiently. This library solves common race-condition issues and allows you to detect multiple button states concurrently without conflicts.

## Features
* **Debouncing:** Built-in software debounce (default 50ms).
* **Non-blocking:** Uses `millis()` entirely. No `delay()` used.
* **Independent States:** Call `clicked()`, `released()`, `as_switch()`, and multi-click readers in the same loop without them stealing each other's state.
* **Multi-Click Detection:** Accurately detects single, double, triple, or N-clicks with a configurable timeout.
* **Long Press:** Detect when a button is held for a specific duration.
* **Repeat Action:** Trigger an action continuously at a set interval while the button is held down.

## Installation
1. Download this repository as a `.zip` file.
2. Open Arduino IDE.
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**
4. Select the downloaded `.zip` file.

## Core Functions

| Function | Description |
| :--- | :--- |
| `init(pin, mode, timeout)` | Initializes the button pin, INPUT/INPUT_PULLUP mode, and multi-click timeout (default 1000ms). |
| `clicked()` | Returns `true` once when the button is pressed down (Edge detection). |
| `released()` | Returns `true` once when the button is released (Edge detection). |
| `clicked_times()` | Evaluates and returns the total number of clicks after the timeout has passed. Resets automatically. |
| `pressed(time_ms)` | Returns `true` once if the button has been held down for `time_ms`. |
| `repeat(interval_ms)`| Returns `true` repeatedly every `interval_ms` as long as the button is held down. |
| `as_switch()` | Toggles and returns `true` or `false` on every click. Acts like a push-on/push-off switch. |
| `get_pressed_time()` | Return how long button is pressed in ms. |
| `get_clicked_times()` | Return how many clicks in n times. |
| `set_debounce_delay(uint16_t debounce_delay = 50)` | Change debounce delay (default 50 ms). |