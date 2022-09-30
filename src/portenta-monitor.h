#ifndef PORTENTA_MONITOR_H
#define PORTENTA_MONITOR_H

#include "portenta-led.h"

//===================================================================================================
// 
//===================================================================================================
#include "mbed.h"
using namespace mbed;
using namespace rtos;

//===================================================================================================
// 
//===================================================================================================
class MPMON {
  private:   
    bool  status = false;  
    long  counter = 1;

    Mutex holdIt;
    Mutex holdItForWhile;
    
    MPMON() = default;  // Make constructor private  

    char text[37] = {'A', 'B', 'C', 'D', 'E', 'F', 
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
    'Y', 'Z','1','2','3','4','5','6','7','8', 
    '9','0',' ' };
 
    std::string morse[36] = {".-","-...","-.-.","-..",".","..-",
    "--.","....","..",".---","-.-",".-..","--","-.","---",
    ".--.","--.-",".-.","...","-","..-","...-",".--","-..-",
    "-.--","--..", ".----","..---","...--","....-",".....","-....","--....","---..",
    "----.","-----"};

  public:
    //SINGLETON
    static MPMON &getInstance();    // Accessor for singleton instance
    MPMON(const MPMON &) = delete;  // no copying
    MPMON &operator=(const MPMON &) = delete;

  public:    
    bool  visible           = true;
    bool  debug             = true;         //enable serial output
    bool  serialPortEnabled = false;

    bool Status();
    bool Init();

    bool Visible(bool state);
    bool Enable(bool state);
    bool Debug(String message);
    bool HoldItForWhile(bool state);

    void MorseCode(std::string phrase);
};

extern MPMON &mpMON;

#endif