/*
  RepeatButton_KeyPress.ino
  Created:  4-Mar-2023
  Author:   MicroBeaut
*/

/*
  The KeyPress event occurs when presses a key
*/

#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyPressed(ButtonEvents e);  // Declare the OnKeyPress Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.onKeyPressed(OnKeyPressed);          // Configure the callback function event on the key pressed
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the repeat button function
  if (button.isKeyPressed()) {
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyPressed(ButtonEvents e) {
  switch (e) {
    case keyPress:
      Serial.println("Event on Key Pressed");   // Print message event on key pressed
      break;
  }
}