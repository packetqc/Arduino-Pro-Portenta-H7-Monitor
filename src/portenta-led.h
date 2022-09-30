#ifndef portentaled_h
#define portentaled_h

#include "Arduino.h"
#include "mbed.h"


#define MEMORY_POOL_SIZE_LED 512


using namespace mbed;
using namespace rtos;

enum led_activities {
  ON,
  OFF,
  DOT,
  DASH,
  UNIT,
  SPACE_LETTER,
  SPACE_WORD,
  GREEN,
  BLUE,
  RED,
  GREEN_ONLY,
  BLUE_ONLY,
  RED_ONLY,
};

//===================================================================================================
// 
//===================================================================================================
class Led
{
  public:
    void Init();
    bool Reset();
    bool ProtectionQueue();
    bool Activity(int todo);
    void Run(void);
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

  public:
    //SINGLETON
    static Led &getInstance();    // Accessor for singleton instance
    Led(const Led &) = delete;  // no copying
    Led &operator=(const Led &) = delete;
    
    MemoryPool<int,MEMORY_POOL_SIZE_LED> ledPool;
    Queue<int,MEMORY_POOL_SIZE_LED> ledActivities;
          
  private:
    Led() = default;
    Thread Led_worker;
    static void Run_callback();    
    bool runit = true;
    Mutex holdIt;

    int _pin;
    int unitTime;
    int unitCharTime;
    int unitWordTime;
};

extern Led &mpLED;


#endif
