#pragma once

#include <Arduino.h>

class Multifunction_Button
{
  private:
    int8_t _button_pin = -1;
    uint16_t _timeout = 1000;
    uint8_t _trigger = HIGH;

    bool _status = false;
    
    bool _pressed_state = false;
    bool _last_pressed_state = false;
    
    unsigned long _pressed_time = 0;
    uint8_t _clicked_times = 0;

    uint16_t _debounce_delay = 50;
    unsigned long _last_debounce_time = 0;

    unsigned long _last_time = 0;
    unsigned long _last_repeat_time = 0;
  
  public:
    Multifunction_Button();

    // Initialize Button Mode
    void init(int8_t button_pin, uint8_t button_mode, uint16_t timeout = 1000);
    // Check if button is pressed
    bool pressed();
    // Check how long button is pressed in time ms
    bool pressed(uint16_t pressed_long);
    // Check if button is clicked
    bool clicked();
    // Check if button is released
    bool released();
    // Check if button is clicked in n times
    bool clicked(uint8_t clicked_times);
    // Repeat button pressed in interval ms
    bool repeat(uint16_t interval);
    // Set debounce delay time in ms
    void set_debounce_delay(uint16_t debounce_delay = 50);
};