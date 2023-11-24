#include <LowPower.h>

const int ledPin = 6;
const int buttonPin = 2;

int mode = 1;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  analogWrite(ledPin, 255);
  Serial.begin(921600);
}

void wakeUp(){
  
}

void loop() {   
// read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) >= 3000){
    mode = 0;
  }
  else if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH){
        if (mode == 3){
          mode = (mode - 2);
        }
        else {
        mode = mode + 1;
      }
    }
    }
  switch (mode) {
    case 0:  //sleep mode
      analogWrite(ledPin, 0);
      attachInterrupt(0, wakeUp, LOW);
      LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
      detachInterrupt(0);
      break;
    case 1:  //25% brightness
      analogWrite(ledPin, 10);
      mode = 1;
      Serial.println(mode);
      break;
    case 2:  //50% brightness
      analogWrite(ledPin, 100);
      mode = 2;
      Serial.println(mode);
      break;
    case 3:  //100% brightness
      analogWrite(ledPin, 255);
      mode = 3;
      Serial.println(mode);
      break;
  }
  }
  lastButtonState = reading;
}