#ifndef portentaled_h
#define portentaled_h

#include "Arduino.h"

class Led
{
  public:
    Led();
    void dot();
    void dash();
    void green(bool state);
    void blue(bool state);
    void red(bool state);
    
  private:
    int _pin;
};


#endif
