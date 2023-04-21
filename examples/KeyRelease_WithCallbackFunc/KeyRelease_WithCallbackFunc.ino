/*
  KeyRelease_WithCallbackFunc.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut

  The KeyRelease event occurs when released a key.
*/

#include "RepeatButton.h"

#define buttonPin 2                     // Define the button input pin.

RepeatButton button;                    // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e); // Declare the OnKeyStateChanged Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.buttonEvents(OnKeyStateChanged);     // Configure the callback function event on the key released
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
}

void OnKeyStateChanged(ButtonEvents e) {
  Serial.println("Callback Event on Key Released");    // Print message event on key Released
}