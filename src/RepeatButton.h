/*
  RepeatButton.cpp
  Created:  4-Mar-2023
  Author:   MicroBeaut
*/

/*
  MIT License
  Copyright (c) 2023 MicroBeaut
*/

#ifndef REPEATBUTTON_H
#define REPEATBUTTON_H

#include "Arduino.h"

enum ButtonEvents {
  keyPress = 1,     // Occurs when a key is pressed
  keyRelease = 2,   // Occurs when a key is released
  keyHold = 3,      // Occurs when a key is hold
  keyRepeat = 4     // Occurs when a key is pressed an hold
};

class RepeatButton {
  private:
#define MS2US(ms) (ms * 1000UL)
    const uint16_t _defaultDebounceDelay  = 10; // Milliseconds
    const uint16_t _defaultHoldDelay = 0;   // Milliseconds
    const uint16_t _defaultRepeatDelay = 500;   // Milliseconds
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

    uint8_t _pin;
    unsigned long _debebounceDelay;
    unsigned long _holdDelay;
    unsigned long _repeatDelay;
    unsigned long _repeatRate;

    unsigned long _startTime;
    unsigned long _startTimeRepeat;

    KeyEventCallback _onKeyPressed = nullptr;
    KeyEventCallback _onKeyReleased = nullptr;
    KeyEventCallback _onKeyHoldingEvent = nullptr;

    void internalDebounce();
    void internalOnPressed();
    void internalOnReleased();
    void internalOnHolding();
    void internalOnRepeatOn();
    void internalOnRepeating();
  public:
    RepeatButton();
    void buttonMode(uint8_t pin, uint8_t mode = INPUT);
    void debounceDelay(uint16_t debounceDelay /*mS*/);
    void repeatDelay(uint16_t repeatDelay /*mS*/, uint16_t repeatRate/*mS*/);
    void holdDelay(uint16_t holdDelay /*mS*/);
    bool repeatButton();
    void onKeyPressed(KeyEventCallback keyPressedEvent = nullptr);
    void onKeyReleased(KeyEventCallback keyReleasedEvent = nullptr);
    void onKeyHolding(KeyEventCallback keyHoldingEvent = nullptr);
    bool isKeyPressed();
    bool isKeyReleased();
    bool isKeyHolding();
    bool isRepeating();
};

#endif // REPEATBUTTON_H