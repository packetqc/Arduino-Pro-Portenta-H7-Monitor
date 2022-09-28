#include "Arduino.h"
#include "portenta-led.h"

Led::Led()
{
  _pin = LED_BUILTIN;
  pinMode(_pin, OUTPUT);
}

void Led::init() {
  green(true);
  delay(1000);
  green(false);
  delay(1000);
  blue(true);
  delay(1000);
  blue(false);
  delay(1000);
  red(true);
  delay(1000);
  red(false);
  delay(1000);

  // green(true);blue(true);red(true);
  // dot(); dot(); dot();
  // delay(1000);
  // dash(); dash();
  // delay(1000);
  // dot(); dot(); dot();
  // delay(1000);
  // green(false);blue(false);red(false);
}

void Led::dot()
{
  digitalWrite(_pin, LOW);
  delay(250);
  digitalWrite(_pin, HIGH);
  delay(250);  
}

void Led::dash()
{
  digitalWrite(_pin, LOW);
  delay(1000);
  digitalWrite(_pin, HIGH);
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
