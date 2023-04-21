/*
  RepeatButton.h
  Created:  4-Mar-2023
  Author:   MicroBeaut

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#include "RepeatButton.h"

RepeatButton::RepeatButton() {
  this->debounceDelay(_defaultDebounceDelay);
  this->holdDelay(_defaultHoldDelay);
  this->repeatDelay(_defaultRepeatDelay, _defaultRepeatRate);
  _input = false;
  _output = false;
  _pressed = false;
  _prevPressed = false;
  _released = false;
  _prevReleased = false;
  _holding = false;
  _prevHolding = false;
  _repeating = false;
  _prevRepeating = false;
  _pullup = false;
}

void RepeatButton::buttonMode(uint8_t pin, uint8_t mode) {
  _pin = pin;
  pinMode(_pin, mode);
  _pullup = mode == INPUT_PULLUP ? true : false;
  _output = _pullup;
  _input = _pullup;
}

void RepeatButton::debounceDelay(uint16_t debounceDelay /*mS*/) {
  _debebounceDelay = MS2US(debounceDelay);
}

void RepeatButton::holdDelay(uint16_t holdDelay /*mS*/) {
  _holdDelay = MS2US(holdDelay);
}

void RepeatButton::repeatDelay(uint16_t repeatDelay /*mS*/, uint16_t repeatRate /*mS*/) {
  _repeatDelay = MS2US(repeatDelay);
  _repeatRate = MS2US(repeatRate);
}

bool RepeatButton::repeatButton() {
  bool input = digitalRead(_pin);
  if (_input != input) {
    _startTime = micros();
    _holding = false;
  }
  _input = input;
  if (_input != _output) {
    this->internalDebounce();
  } else {
    if ( _pressed ) {
      this->internalOnRepeatOn();
      this->internalOnRepeating();
      this->internalOnHolding();
    }
  }
  return _output;
}

void RepeatButton::internalDebounce() {
  if (_debebounceDelay <= 0UL) return;
  unsigned long elapsedTime = micros() - _startTime;
  if (elapsedTime >= _debebounceDelay) {
    if ( _input != _pullup ) {
      _startRepeatTime = micros();
      this->internalOnPressed();
    } else {
      this->internalOnReleased();
    }
    _output = _input;
  }
}

void RepeatButton::internalOnPressed() {
  _pressed = true;
  _released = false;
  this->internalButtonEvents(PRESS);
}

void RepeatButton::internalOnReleased() {
  _pressed = false;
  _released = true;
  _repeating = false;
  this->internalButtonEvents(RELEASE);
}

void RepeatButton::internalOnHolding() {
  _holding = this->internalEventTimer(_holding, _startTime, _holdDelay, HOLD, false);
}

void RepeatButton::internalOnRepeatOn() {
  _repeating = this->internalEventTimer(_repeating, _startRepeatTime, _repeatDelay, REPEAT, true);
}

void RepeatButton::internalOnRepeating() {
  this->internalEventTimer(!_repeating, _startRepeatTime, _repeatRate, REPEAT, true);
}

void RepeatButton::internalButtonEvents(ButtonEvents buttonEvent) {
  if (_buttonEvents) {
    _buttonEvents(buttonEvent);
  }
}

bool RepeatButton::internalEventTimer(bool input, unsigned long &startTime, unsigned long delayTime, ButtonEvents buttonEvent, bool repeat) {
  if (input) return input;
  if (delayTime <= 0UL) return input;

  unsigned long elapsedTime = micros() - startTime;
  if (elapsedTime >= delayTime) {
    if (repeat) startTime = micros();
    this->internalButtonEvents(buttonEvent);
    return true;
  }
  return false;
}

void RepeatButton::buttonEvents(KeyEventCallback keyEventCallback) {
  _buttonEvents = keyEventCallback;
}

bool RepeatButton::isPressed(bool steadyState) {
  if (steadyState) return _pressed;
  _dummyState = _prevPressed;
  _prevPressed = _pressed;
  return _pressed & !_dummyState;
}

bool RepeatButton::isReleased(bool steadyState) {
  if (steadyState) return _released;
  _dummyState = _prevReleased;
  _prevReleased = _released;
  return _released & !_dummyState;
}

bool RepeatButton::isHold(bool steadyState)  {
  if (steadyState) return _holding;
  _dummyState = _prevHolding;
  _prevHolding = _holding;
  return _holding & !_dummyState;
}

bool RepeatButton::isRepeat(bool steadyState) {
  if (steadyState) return _repeating;
  _dummyState = _prevRepeating;
  _prevRepeating = _repeating;
  return  _repeating & !_dummyState;
}