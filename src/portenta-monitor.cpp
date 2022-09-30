#include "portenta-monitor.h"
#include "portenta-led.h"

#include <string>
#include <iostream>
#include <algorithm>

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Status() {
  return status;
}

//===================================================================================================
// 
//===================================================================================================
void MPMON::MorseCode(std::string phrase) {
  
  mpMON.Debug(String("[MORSE CODE] ")+phrase.c_str());

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
            // mpLED.dot();
            mpLED.Activity(DOT);
          }
          else if(toMorse.at(j) == '-') {
            // mpLED.dash();
            mpLED.Activity(DASH);
          }

          if( j != toMorse.length()-1 ) {
            // mpLED.unit();
            mpLED.Activity(UNIT);
          }
        }
      }
    }

    if( i != phrase.length()-1 ) {
        if(phrase.at(i+1) == ' ') {
          // mpLED.spaceWord();
          mpLED.Activity(SPACE_WORD);
        }
        else {
          // mpLED.spaceLetter();
          mpLED.Activity(SPACE_LETTER);
        }
      }
  }

}

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Visible(bool state) {
  visible = state;
  return visible;
}

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Enable(bool state) {
  debug = state;
  return debug;
}

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Init() {
  bool retour = false;

  if(visible) {
    mpLED.Init();
    mpLED.Run();
    mpLED.Activity(DASH);
  }

  if(debug) {
    Serial.begin(115200);
    
    while(!Serial) {
      if(visible)
        // mpLED.dot();
        mpLED.Activity(DOT);
      delay(5000);
    }
    
    if(Serial) {
      serialPortEnabled = true;
      Serial.println("DEBUG: serial port started");
    }        
  }

  status = true;

  retour = true;

  return retour;
}

//===================================================================================================
// 
//===================================================================================================
bool MPMON::HoldItForWhile(bool state) {
  if(state) {
    holdItForWhile.lock();
  }
  else {
    holdItForWhile.unlock();
  }
}

//===================================================================================================
// 
//===================================================================================================
bool MPMON::Debug(String incoming) {
  bool retour = true;
  long ticket = counter++;

  if(debug) {
    if(serialPortEnabled) {    
      holdIt.lock();      

      if(incoming.length() > 0)    
        Serial.print(String("DEBUG: [")+ticket+String("] "));
        
      Serial.println(incoming);

      holdIt.unlock();
    }
  }
     
  // if(visible) {
  //   mpLED.Activity(BLUE);
  // }      
  
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
