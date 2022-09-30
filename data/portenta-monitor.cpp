#include "portenta-monitor.h"

#include <string>
#include <iostream>
#include <algorithm>

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Status() {
  return status;
}

void MPMON::MorseCode(String phrase) {
  std::transform(phrase.begin(), phrase.end(), phrase.begin(), ::toupper);
  for (int i = 0; i<phrase.length(); ++i) {
    for (int counter = 0; counter < 36; counter++) {
      if (phrase.charAt(i) == text[counter]) {
        String toMorse = ""+morse[i];
        
        for(int j=0; j<toMorse.length(); j++) {
          if(toMorse.charAt(j) == '.') {
            led.dot();
          }
          else if(toMorse.charAt(j) == '-') {
            led.dash();
          }
        }
      }
    }
  }
}

bool MPMON::Visible(bool state) {
  visible = state;
  return visible;
}

bool MPMON::Enable(bool state) {
  debug = state;
  return debug;
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
