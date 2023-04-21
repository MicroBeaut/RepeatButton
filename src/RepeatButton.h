/*
  RepeatButton.cpp
  Created:  4-Mar-2023
  Author:   MicroBeaut

  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#ifndef REPEATBUTTON_H
#define REPEATBUTTON_H

#include "Arduino.h"

enum ButtonEvents {
  PRESS = 1,     // Occurs when a key is pressed
  RELEASE = 2,   // Occurs when a key is released
  HOLD = 3,      // Occurs when a key is hold
  REPEAT = 4     // Occurs when a key is pressed an hold
};

class RepeatButton {
  private:
#define MS2US(ms) (ms * 1000UL)
    const uint16_t _defaultDebounceDelay  = 10; // Milliseconds
    const uint16_t _defaultHoldDelay = 0;       // Milliseconds
    const uint16_t _defaultRepeatDelay = 0;     // Milliseconds
    const uint16_t _defaultRepeatRate = 250;    // Milliseconds
    // Event Handler
    typedef void (*KeyEventCallback) (ButtonEvents e);

    unsigned char _input: 1;
    unsigned char _output: 1;
    unsigned char _pressed: 1;
    unsigned char _released: 1;
    unsigned char _holding: 1;
    unsigned char _repeating: 1;
    unsigned char _pullup: 1;
    unsigned char _prevPressed : 1;
    unsigned char _prevReleased : 1;
    unsigned char _prevHolding : 1;
    unsigned char _prevRepeating : 1;
    unsigned char _dummyState : 1;

    uint8_t _pin;
    unsigned long _debebounceDelay = 0;
    unsigned long _holdDelay = 0;
    unsigned long _repeatDelay = 0;
    unsigned long _repeatRate = 0;

    unsigned long _startTime = 0;
    unsigned long _startRepeatTime = 0;

    KeyEventCallback _buttonEvents = nullptr;

    void internalDebounce();
    void internalOnPressed();
    void internalOnReleased();
    void internalOnHolding();
    void internalOnRepeatOn();
    void internalOnRepeating();
    void internalButtonEvents(ButtonEvents buttonEvent);
    bool internalEventTimer(bool input, unsigned long &startTime, unsigned long delayTime, ButtonEvents buttonEvent, bool repeat);
  public:
    RepeatButton();
    void buttonMode(uint8_t pin, uint8_t mode);
    void debounceDelay(uint16_t debounceDelay /*mS*/);
    void repeatDelay(uint16_t repeatDelay /*mS*/, uint16_t repeatRate/*mS*/);
    void holdDelay(uint16_t holdDelay /*mS*/);
    bool repeatButton();
    void buttonEvents(KeyEventCallback keyEventCallback);
    bool isPressed(bool SteadyState = 0);
    bool isReleased(bool SteadyState = 0);
    bool isHold(bool SteadyState = 0);
    bool isRepeat(bool SteadyState = 0);
};

#endif // REPEATBUTTON_H
