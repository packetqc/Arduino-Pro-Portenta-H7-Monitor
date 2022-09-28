#ifndef portentaled_h
#define portentaled_h

#include "Arduino.h"

class Led
{
  public:
    Led();
    void on();
    void off();
    void dot();
    void dash();
    void unit();
    void spaceLetter();
    void spaceWord();
    void green(bool state);
    void blue(bool state);
    void red(bool state);
    
  private:
    int _pin;
    int unitTime;
    int unitCharTime;
    int unitWordTime;
};


#endif
