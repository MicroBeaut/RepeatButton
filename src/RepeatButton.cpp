/*
  RepeatButton.h
  Created:  4-Mar-2023
  Author:   MicroBeaut
*/

/*
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
  if (_onKeyPressed) {
    _onKeyPressed(keyPress);
  }
}

void RepeatButton::internalOnReleased() {
  _pressed = false;
  _released = true;
  _repeating = false;
  if (_onKeyReleased) {
    _onKeyReleased(keyRelease);
  }
}

void RepeatButton::internalOnHolding() {
  if (_holding) return;
  if (_holdDelay <= 0UL) return;

  unsigned long elapsedTime = micros() - _startTime;
  if (elapsedTime >= _holdDelay) {
    _holding = true;
    if (_onKeyHoldingEvent) {
      _onKeyHoldingEvent(keyRelease);
    }
  }
}

void RepeatButton::internalOnRepeatOn() {
  if (_repeating) return;
  if (_repeatDelay <= 0UL) return;

  unsigned long elapsedTime = micros() - _startRepeatTime;
  if (elapsedTime >= _repeatDelay) {
    _startRepeatTime = micros();
    _repeating = true;
    if (_onKeyPressed) {
      _onKeyPressed(keyRepeat);
    }
  }
}

void RepeatButton::internalOnRepeating() {
  if (!_repeating) return;
  if (_repeatRate <= 0UL) return;

  unsigned long elapsedTime = micros() - _startRepeatTime;
  if (elapsedTime >= _repeatRate) {
    _startRepeatTime = micros();
    if (_onKeyPressed) {
      _onKeyPressed(keyRepeat);
    }
  }
}

void RepeatButton::onKeyPressed(KeyEventCallback keyPressedEvent) {
  _onKeyPressed = keyPressedEvent;
}

void RepeatButton::onKeyReleased(KeyEventCallback keyReleasedEvent) {
  _onKeyReleased = keyReleasedEvent;
}

void RepeatButton::onKeyHolding(KeyEventCallback keyHoldEvent) {
  _onKeyHoldingEvent = keyHoldEvent;
}

bool RepeatButton::isKeyPressed(bool steadyState) {
  if (steadyState) return _pressed;
  _dummyState = _prevPressed;
  _prevPressed = _pressed;
  return _pressed & !_dummyState;
}

bool RepeatButton::isKeyReleased(bool steadyState) {
  if (steadyState) return _released;
  _dummyState = _prevReleased;
  _prevReleased = _released;
  return _released & !_dummyState;
}

bool RepeatButton::isKeyHolding(bool steadyState)  {
  if (steadyState) return _holding;
  _dummyState = _prevHolding;
  _prevHolding = _holding;
  return _holding & !_dummyState;
}

bool RepeatButton::isRepeating(bool steadyState) {
  if (steadyState) return _repeating;
  _dummyState = _prevRepeating;
  _prevRepeating = _repeating;
  return  _repeating & !_dummyState;
}