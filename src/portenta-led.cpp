#include "Arduino.h"
#include "portenta-led.h"

Led::Led()
{
  unitTime = 250;
  unitCharTime = unitTime*3;
  unitWordTime = unitTime*7;

  _pin = LED_BUILTIN;
  pinMode(_pin, OUTPUT);
}

void Led::on() {
  digitalWrite(_pin, LOW);
}

void Led::off() {
  digitalWrite(_pin, HIGH);
}

void Led::unit() {
  delay(unitTime);
}

void Led::spaceLetter() {
  delay(unitCharTime);
}

void Led::spaceWord() {
  delay(unitWordTime);
}

void Led::dot()
{
  digitalWrite(_pin, LOW);
  unit();
  digitalWrite(_pin, HIGH);
}

void Led::dash()
{
  digitalWrite(_pin, LOW);
  spaceLetter();
  digitalWrite(_pin, HIGH);
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
