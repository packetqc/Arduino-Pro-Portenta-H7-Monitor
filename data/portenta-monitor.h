#pragma once

#include "portenta-led.h"


class MPMON {
  private:   
    bool  status;  
    
    MPMON() = default;  // Make constructor private  

  public:
    //SINGLETON
    static MPMON &getInstance();    // Accessor for singleton instance
    MPMON(const MPMON &) = delete;  // no copying
    MPMON &operator=(const MPMON &) = delete;

  public:    
    bool  visible           = true;
    bool  debug             = true;         //enable serial output
    bool  serialPortEnabled = false;
    Led   led;

    bool Status();
    bool Init();
    bool Debug(String message);

};

extern MPMON &mpMON;
