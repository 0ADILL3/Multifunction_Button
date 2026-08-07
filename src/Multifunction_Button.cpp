#include "Multifunction_Button.h"

Multifunction_Button::Multifunction_Button() {}

void Multifunction_Button::init(int8_t button_pin, uint8_t button_mode, uint16_t timeout)
{
  button_pin_ = button_pin;
  timeout_ = timeout;
  trigger_ = (button_mode == INPUT_PULLUP) ? LOW : HIGH;

  pinMode(button_pin_, button_mode);
}

bool Multifunction_Button::pressed()
{
  if (digitalRead(button_pin_) == trigger_)
  {  
    last_time_ = millis();

    if (!pressed_state_ && (millis() - last_debounce_time_ > debounce_delay_))
    {
      pressed_state_ = true;
      last_debounce_time_ = millis();
    }
  }
  else
  {
    if (pressed_state_ && (millis() - last_debounce_time_ > debounce_delay_)) 
    {
      pressed_state_ = false;
      last_debounce_time_ = millis();
    }
  }

  return pressed_state_;
}

bool Multifunction_Button::pressed(uint16_t pressed_long)
{
  if (pressed())
  {
    if (millis() - pressed_time_ > pressed_long)
    {
      clicked_times_ = 0;
      return true;
    }
    else {return false;}
  }
  else
  {
    pressed_time_ = millis();
    return false;
  }
}

bool Multifunction_Button::clicked()
{
  pressed();
  
  if (pressed_state_ != last_clicked_state_ && pressed_state_ == true)
  {
    last_clicked_state_ = pressed_state_;
    return true;
  }
  else
  {
    last_clicked_state_ = pressed_state_;
    return false;
  }
}

bool Multifunction_Button::released()
{
  pressed();

  if (pressed_state_ != last_released_state_ && pressed_state_ == false)
  {
    last_released_state_ = pressed_state_;
    return true;
  }
  else
  {
    last_released_state_ = pressed_state_;
    return false;
  }
}

uint8_t Multifunction_Button::clicked_times()
{
  pressed();
  
  if (pressed_state_ != last_multiclicked_state_ && pressed_state_ == true)
  {
    clicked_times_++;
    last_multiclicked_state_ = pressed_state_;
  }
  else
  {
    last_multiclicked_state_ = pressed_state_;
  }

  if (clicked_times_ > 0 && (millis() - last_time_ > timeout_))
  {
    uint8_t final_clicks = clicked_times_; 
    clicked_times_ = 0; 
    return final_clicks; 
  }

  return 0;
}

bool Multifunction_Button::repeat(uint16_t interval)
{
  if (pressed())
  {
    if (millis() - last_repeat_time_ > interval)
    {
      last_repeat_time_ = millis();
      clicked_times_ = 0;
      return true;
    }
  }
  else
  {
    pressed_time_ = millis();
    last_repeat_time_ = millis();
  }
  
  return false;
}

bool Multifunction_Button::as_switch()
{
  pressed();
  
  if (pressed_state_ != last_switch_state_ && pressed_state_ == true)
  {
    switch_state_ = !switch_state_;
    last_switch_state_ = pressed_state_;
  }
  else
  {
    last_switch_state_ = pressed_state_;
  }

  return switch_state_;
}

unsigned long Multifunction_Button::get_pressed_time() {return (millis() - pressed_time_);}

uint8_t Multifunction_Button::get_clicked_times() {return clicked_times_;}

void Multifunction_Button::set_debounce_delay(uint16_t debounce_delay) {debounce_delay_ = debounce_delay;}