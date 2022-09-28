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

void MPMON::MorseCode(std::string phrase) {
  std::transform(phrase.begin(), phrase.end(), phrase.begin(), ::toupper);

  for (int i = 0; i<phrase.length(); i++) {
    for (int counter = 0; counter < 37; counter++) {
      if (phrase.at(i) == text[counter]) {

        std::string toMorse;
        if(counter != 36)
          toMorse = (std::string)morse[counter].c_str();
        else
          continue;

        for(int j=0; j<toMorse.length(); j++) {
          if(toMorse.at(j) == '.') {
            led.dot();
          }
          else if(toMorse.at(j) == '-') {
            led.dash();
          }

          if( j != toMorse.length()-1 ) {
            led.unit();
          }
        }
      }
    }

    if( i != phrase.length()-1 ) {
        if(phrase.at(i+1) == ' ') {
          led.spaceWord();
        }
        else {
          led.spaceLetter();
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
    led.unit();   
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
