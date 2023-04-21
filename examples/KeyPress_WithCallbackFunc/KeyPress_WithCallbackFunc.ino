/*
  KeyPress_WithCallbackFunc.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut

  The KeyPress event occurs when presses a key
*/

#include "RepeatButton.h"

#define buttonPin 2                     // Define the button input pin.

RepeatButton button;                    // Decalre the RepeatButton object

void OnKeyStateChanged(ButtonEvents e); // Declare the OnKeyStateChanged Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.buttonEvents(OnKeyStateChanged);     // Configure the callback function event on the key pressed
}

void loop() {
  button.repeatButton();                      // Executing the repeat button function
}

void OnKeyStateChanged(ButtonEvents e) {
  switch (e) {
    case PRESS:
      Serial.println("Callback Event on Key Pressed");  // Print message event on key pressed
      break;
  }
}