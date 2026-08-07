#pragma once

#include <Arduino.h>

class Multifunction_Button
{
  private:
    int8_t button_pin_ = -1;
    uint16_t timeout_ = 1000;
    uint8_t trigger_ = HIGH;
    
    bool pressed_state_ = false;
    bool last_clicked_state_ = false;
    bool last_released_state_ = false;
    bool last_multiclicked_state_ = false;
    bool last_switch_state_ = false;
    
    unsigned long pressed_time_ = 0;
    uint8_t clicked_times_ = 0;
    bool switch_state_ = false;

    uint16_t debounce_delay_ = 50;
    unsigned long last_debounce_time_ = 0;

    unsigned long last_time_ = 0;
    unsigned long last_repeat_time_ = 0;
  
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
    uint8_t clicked_times();
    // Repeat button pressed in interval ms
    bool repeat(uint16_t interval);
    // Make button act like a switch
    bool as_switch();
    // Get pressed time in ms
    unsigned long get_pressed_time();
    // Get clicked times in n times
    uint8_t get_clicked_times();
    // Set debounce delay time in ms
    void set_debounce_delay(uint16_t debounce_delay = 50);
};