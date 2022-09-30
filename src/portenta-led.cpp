#include "Arduino.h"
#include "portenta-led.h"
#include "portenta-monitor.h"

//===================================================================================================
// 
//===================================================================================================
void Led::Init()
{
  unitTime = 250;
  unitCharTime = unitTime*3;
  unitWordTime = unitTime*7;

  _pin = LED_BUILTIN;
  pinMode(_pin, OUTPUT);

}

//===================================================================================================
// 
//===================================================================================================
bool Led::Reset() {
  bool retour = true;

  holdIt.lock();
  mpMON.Debug("[LED][SEC] Buffer protection: reseting queue to empty");

  while(!ledActivities.empty()) {
    osEvent evt = mpLED.ledActivities.get();
    if(evt.status == osEventMessage) {
      int *todo = (int*)evt.value.p;
      mpLED.ledPool.free(todo);
      mpMON.Debug(String("[LED][SEC] Activity count: ")+mpLED.ledActivities.count());
    }
  }

  mpMON.Debug("[LED][SEC] Buffer protection: activity queue is empty");
  mpMON.Debug(String(""));

  holdIt.unlock();

  return retour;
}

//===================================================================================================
// 
//===================================================================================================
bool Led::ProtectionQueue() {
  bool retour = false;

  if(ledActivities.full()) {
    retour = true;
    mpMON.Debug("[LED][SEC] Buffer protection: activity queue is full");
  }

  return retour;
}

//===================================================================================================
// 
//===================================================================================================
bool Led::Activity(int todo) {
  bool retour = true;

  if(!ProtectionQueue()) {
    holdIt.lock();
    int *it = mpLED.ledPool.alloc();
    *it = todo;

    mpLED.ledActivities.put(it);
    holdIt.unlock();
  }
  else {
    retour = false;
  }

  return retour;
}

//===================================================================================================
// 
//===================================================================================================
void Led::Run(void) {
    runit = true;    
    Led_worker.start(callback(Run_callback));
}

//===================================================================================================
// SINGLETON
//===================================================================================================
Led &Led::getInstance() {
  static Led instance;
  return instance;
}

Led &mpLED = mpLED.getInstance();

//===================================================================================================
// WORKER
//===================================================================================================
void Led::Run_callback() {
    while (mpLED.runit)
    {
      while(!mpLED.ledActivities.empty()) {
        
        // if(mpMON.Status()) {
        //   // Serial.println(String("Led activity: ")+*todo);    
        //   mpMON.Debug(String("[LED] Activity count: ")+mpLED.ledActivities.count());
        //   mpMON.Debug(String(""));
        // }
      
        osEvent evt = mpLED.ledActivities.get();

        // if(mpMON.Status()) {
        //   // Serial.println(String("Led activity: ")+*todo);    
        //   mpMON.Debug(String("[LED] Activity count: ")+mpLED.ledActivities.count());
        //   mpMON.Debug(String(""));
        // }

        if(evt.status == osEventMessage) {
          int *todo = (int*)evt.value.p;
          
          // if(mpMON.Status()) {
          //   // Serial.println(String("Led activity: ")+*todo);    
          //   mpMON.Debug(String("[LED] Led activity: ")+*todo);
          //   mpMON.Debug(String(""));
          // }

          switch (*todo)
          {
          case 0:
            mpLED.on();
            break;
          
          case 1:
            mpLED.off();
            break;
          
          case 2:
            mpLED.dot();
            break;
          
          case 3:
            mpLED.dash();
            break;
          
          case 4:
            mpLED.unit();
            break;
          
          case 5:
            mpLED.spaceLetter();
            break;
          
          case 6:
            mpLED.spaceWord();
            break;
          
          case 7:
            // mpLED.green();
            break;
          
          case 8:
            // mpLED.blue();
            break;
          
          case 9:
            // mpLED.red();
            break;
          
          case 10:
            // mpLED.greenOnly();
            break;
          
          case 11:
            // mpLED.blueOnly();
            break;
          
          case 12:
            // mpLED.redOnly();
            break;
          
          default:
            // mpLED.dot();
            break;
          }          
          
          mpLED.ledPool.free(todo);
        }        
      }
      yield();
    }    
}

//===================================================================================================
// 
//===================================================================================================
void Led::on() {
  digitalWrite(_pin, LOW);
}

//===================================================================================================
// 
//===================================================================================================
void Led::off() {
  digitalWrite(_pin, HIGH);
}

//===================================================================================================
// 
//===================================================================================================
void Led::unit() {
  delay(unitTime);
  // #if MBED_MAJOR_VERSION == 2
  //     wait_ms(unitTime);
  // #elif MBED_MAJOR_VERSION == 5
  //     thread_sleep_for(unitTime);
  // #else
  //     ThisThread::sleep_for(unitTime);
  // #endif
}

//===================================================================================================
// 
//===================================================================================================
void Led::spaceLetter() {
  delay(unitCharTime);
  // #if MBED_MAJOR_VERSION == 2
  //     wait_ms(unitCharTime);
  // #elif MBED_MAJOR_VERSION == 5
  //     thread_sleep_for(unitCharTime);
  // #else
  //     ThisThread::sleep_for(unitCharTime);
  // #endif  
}

//===================================================================================================
// 
//===================================================================================================
void Led::spaceWord() {
  delay(unitWordTime);
  // #if MBED_MAJOR_VERSION == 2
  //     wait_ms(unitWordTime);
  // #elif MBED_MAJOR_VERSION == 5
  //     thread_sleep_for(unitWordTime);
  // #else
  //     ThisThread::sleep_for(unitWordTime);
  // #endif    
}

//===================================================================================================
// 
//===================================================================================================
void Led::dot()
{
  digitalWrite(_pin, LOW);
  unit();
  digitalWrite(_pin, HIGH);
}

//===================================================================================================
// 
//===================================================================================================
void Led::dash()
{
  digitalWrite(_pin, LOW);
  spaceLetter();
  digitalWrite(_pin, HIGH);
}

//===================================================================================================
// 
//===================================================================================================
void Led::green(bool state) {
  if(state) {
    digitalWrite(LEDG, LOW);
  }
  else {
    digitalWrite(LEDG, HIGH);
  }  
}

//===================================================================================================
// 
//===================================================================================================
void Led::blue(bool state) {
  if(state) {
    digitalWrite(LEDB, LOW);
  }
  else {
    digitalWrite(LEDB, HIGH);
  }  
}

//===================================================================================================
// 
//===================================================================================================
void Led::red(bool state) {
  if(state) {
    digitalWrite(LEDR, LOW);
  }
  else {
    digitalWrite(LEDR, HIGH);
  }
}
