#include "Multifunction_Button.h"

Multifunction_Button::Multifunction_Button() {}

void Multifunction_Button::init(int8_t button_pin, uint8_t button_mode, uint16_t timeout)
{
  _button_pin = button_pin;
  _timeout = timeout;
  _trigger = (button_mode == INPUT_PULLUP) ? LOW : HIGH;

  pinMode(_button_pin, button_mode);
}

bool Multifunction_Button::pressed()
{
  if (_pressed_state) {_last_time = millis();}
  
  if (digitalRead(_button_pin) == _trigger)
  {  
    if (!_pressed_state && (millis() - _last_debounce_time > _debounce_delay))
    {
      _pressed_state = true;
      _last_debounce_time = millis();
    }
  }
  else
  {
    if (_pressed_state && (millis() - _last_debounce_time > _debounce_delay)) 
    {
      _pressed_state = false;
      _last_debounce_time = millis();
    }
  }

  return _pressed_state;
}

bool Multifunction_Button::pressed(uint16_t pressed_long)
{
  if (pressed())
  {
    _status = (millis() - _pressed_time > pressed_long);
  }
  else
  {
    _pressed_time = millis();
    _status = false;
  }

  return _status;
}

bool Multifunction_Button::clicked()
{
  pressed();
  
  if (_pressed_state != _last_pressed_state && _pressed_state == true)
  {
    _last_pressed_state = _pressed_state;
    return true;
  }
  else
  {
    _last_pressed_state = _pressed_state;
    return false;
  }
}

bool Multifunction_Button::released()
{
  pressed();

  if (_pressed_state != _last_pressed_state && _pressed_state == false)
  {
    _last_pressed_state = _pressed_state;
    return true;
  }
  else
  {
    _last_pressed_state = _pressed_state;
    return false;
  }
}

bool Multifunction_Button::clicked(uint8_t clicked_times)
{
  if (clicked()) {_clicked_times++;}

  _status = (_clicked_times == clicked_times) ? true : false;

  if (millis() - _last_time > _timeout)
  {
    _last_time = millis();
    _clicked_times = 0;
    return _status;
  }
  else
  {
    return false;
  }
}

bool Multifunction_Button::repeat(uint16_t interval)
{
  if (pressed())
  {
    if (millis() - _last_repeat_time > interval)
    {
      _last_repeat_time = millis();
      return true;
    }
  }
  else
  {
    _pressed_time = millis();
    _last_repeat_time = millis();
  }
  
  return false;
}

void Multifunction_Button::set_debounce_delay(uint16_t debounce_delay)
{
  _debounce_delay = debounce_delay;
}