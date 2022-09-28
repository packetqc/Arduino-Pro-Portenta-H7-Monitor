#include "Arduino.h"
#include "portenta-led.h"

Led::Led()
{
  _pin = LED_BUILTIN;
  pinMode(_pin, OUTPUT);
}

void Led::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Led::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}

void Led::green(bool state) {
  if(state) {
    digitalWrite(LEDG, LOW);
  }
  else {
    digitalWrite(LEDG, HIGH);
  }  
}

void Led::blue(bool state) {
  if(state) {
    digitalWrite(LEDB, LOW);
  }
  else {
    digitalWrite(LEDB, HIGH);
  }  
}

void Led::red(bool state) {
  if(state) {
    digitalWrite(LEDR, LOW);
  }
  else {
    digitalWrite(LEDR, HIGH);
  }
}
