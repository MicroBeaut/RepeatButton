# RepeatButton
RepeatButton represents a control that raises its press event repeatedly from the time it is pressed until it is released. The `repeatDelay` property determines when the event begins. You can also control the repeat rate of the repetitions with the `repeat rate` property.
- [Syntax](#syntax)
  - [Declaration](#declaration)
  - [Button Events](#button-events)
  - [Execute](#execute)
  - [Parameters](#parameters)
  - [Events](#events)
  - [Returns](#returns)
- [Examples](#examples)
    - [Key Press and onKeyPressed](#key-press-and-onkeypressed)
    - [Key Release and onKeyReleased](#key-release-and-onkeyreleased)
    - [Key Hold and onKeyHolding](#key-hold-and-onkeyholding)
    - [Key Repeat and onKeyRepeating](#key-repeat-and-onkeyrepeating)

## Syntax

### Declaration
```C
RepeatButton repeatButtonVariable;
```

### Button Events
```C
enum ButtonEvents {
  keyPress = 1,     // Occurs when a key is pressed
  keyRelease = 2,   // Occurs when a key is released
  keyHold = 3,      // Occurs when a key is hold
  keyRepeat = 4     // Occurs when a key is pressed an hold
};
```

### Execute
```C
bool repeatButton();    // Executing the Repeat button function
```

### Parameters
```C
void buttonMode(uint8_t pin, uint8_t mode /*INPUT | INPUT_PULLUP*/);
void debounceDelay(uint16_t debounceDelay /*mS*/);
void repeatDelay(uint16_t repeatDelay /*mS*/, uint16_t repeatRate/*mS*/);
```

### Events
```C
void onKeyPressed(KeyEventCallback keyPressedEvent);    // Occurs when a key is pressed and repeat
void onKeyReleased(KeyEventCallback keyReleasedEvent);  // Occurs when a key is released
void onKeyHolding(KeyEventCallback keyHoldingEvent);    // Occurs when a key is hold

// typedef void (*KeyEventCallback) (ButtonEvents e);
```

### Returns
```C
bool isKeyPressed();    // Determines whether the specified key is pressed
bool isKeyReleased();   // Determines whether the specified key is release
bool isKeyHolding();    // Determines whether the specified key is holding
bool isRepeating();     // Determines whether the specified key is repeating
```

## Examples

### Key Press and onKeyPressed

```C
#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyReleased(ButtonEvents e); // Declare the OnKeyReleased Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.onKeyReleased(OnKeyReleased);        // Configure the callback function event on the key released
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isKeyReleased()) {
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyReleased(ButtonEvents e) {
  Serial.println("Event on Key Released");    // Print message event on key Released
}
```

### Key Release and onKeyReleased
```C
#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyReleased(ButtonEvents e); // Declare the OnKeyReleased Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.onKeyReleased(OnKeyReleased);        // Configure the callback function event on the key released
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isKeyReleased()) {
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyReleased(ButtonEvents e) {
  Serial.println("Event on Key Released");    // Print message event on key Released
}
```

### Key Hold and onKeyHolding
```C
#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t holdDelay = 3000;    // Set Hold Time 3000 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyHolding(ButtonEvents e); // Declare the OnKeyHolding Callback Function

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP); // Set the button mode
  button.holdDelay(holdDelay);                // Set the Hold delay
  button.onKeyHolding(OnKeyHolding);          // Configure the callback function event on the key holding
  pinMode(LED_BUILTIN, OUTPUT);               // Set the LED_BUILTIN mode
}

void loop() {
  button.repeatButton();                      // Executing the Repeat button function
  if (button.isKeyHolding()) {
    digitalWrite(LED_BUILTIN, HIGH);          // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);           // Turned LED OFF
  }
}

void OnKeyHolding(ButtonEvents e) {
  Serial.println("Event on Key Hold");    // Print message event on key Hold
}
```

### Key Repeat and onKeyRepeating

```C
#include "RepeatButton.h"

#define buttonPin 2                 // Define the button input pin.

const uint16_t repeatDelay = 500;   // Set Delay 500 milliseconds
const uint16_t repeatRate = 100;    // Set Repeat rate 200 milliseconds

RepeatButton button;                // Decalre the RepeatButton object

void OnKeyPressed(ButtonEvents e); // Declare the OnKeyPressed Callback Function for the repeating option.

void setup() {
  Serial.begin(115200);
  button.buttonMode(buttonPin, INPUT_PULLUP);   // Set the button mode
  button.repeatDelay(repeatDelay, repeatRate);  // Set the Hold delay
  button.onKeyPressed(OnKeyPressed);            // Configure the callback function event on the key holding
  pinMode(LED_BUILTIN, OUTPUT);                 // Set the LED_BUILTIN mode

}

void loop() {
  button.repeatButton();                        // Executing the Repeat button function
  if (button.isRepeating()) {
    digitalWrite(LED_BUILTIN, HIGH);            // Turned LED ON
  } else {
    digitalWrite(LED_BUILTIN, LOW);             // Turned LED OFF
  }
}

void OnKeyPressed(ButtonEvents e) {
  switch (e) {
    case keyPress:
      Serial.println("Event on Key Pressed");   // Print message event on key pressed
      break;
    case keyRepeat:
      Serial.println("Event on Key Repeat");    // Print message event on key repeat                          
      break;
  }
}
```