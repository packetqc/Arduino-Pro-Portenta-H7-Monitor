#include "portenta-monitor.h"

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Status() {
  return status;
}

bool MPMON::Init() {
  bool retour = false;

  if(debug) {
    Serial.begin(115200);
    
    while(!Serial) {
      led.dot();
      delay(5000);
    }
    
    if(Serial) {
      serialPortEnabled = true;
      Serial.println("DEBUG: serial port started");
    }        
  }

  retour = true;

  return retour;
}

bool MPMON::Debug(String incoming) {
  bool retour = true;

  if(debug) {
    if(serialPortEnabled) {        
      Serial.print("DEBUG: ");
      Serial.println(incoming);
    }
  }
      
  if(visible) {
    led.dot();    
    led.dot();     
  }      
  
  return retour;  
}

//===================================================================================================
// SINGLETON
//===================================================================================================
MPMON &MPMON::getInstance() {
  static MPMON instance;
  return instance;
}

MPMON &mpMON = mpMON.getInstance();
