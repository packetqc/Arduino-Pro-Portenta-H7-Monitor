#include "src/portenta-monitor.h"
#include "src/portenta-performance.h"

//===================================================================================================
// 
//===================================================================================================
void setup() {
  // mpMON.Enable(false);
  // mpMON.Visible(false);
  
  mpMON.Init();
  mpMON.Debug("Message 1");
  
  mpPERF.Run();

  // //===================================================================================================
  // // 
  // //===================================================================================================
  // #if MBED_MAJOR_VERSION == 2
  //     wait_ms(5000);
  // #elif MBED_MAJOR_VERSION == 5
  //     thread_sleep_for(5000);
  // #else
  //     ThisThread::sleep_for(5000);
  // #endif

  // bool testQueue = true;
  // while(testQueue) {
  //   if(!mpLED.ProtectionQueue()) {
  //     mpMON.MorseCode("sos sos");          
  //   } 
  //   else {
  //     testQueue = false;
  //     mpLED.Reset();
  //   }      
  // }

  //===================================================================================================
  // 
  //===================================================================================================
  while(true) {   
    mpMON.MorseCode("sos sos");          
    
    #if MBED_MAJOR_VERSION == 2
        wait_ms(30000);
    #elif MBED_MAJOR_VERSION == 5
        thread_sleep_for(30000);
    #else
        ThisThread::sleep_for(30000);
    #endif
  }
  
  //===================================================================================================
  // 
  //===================================================================================================
  // mpMON.Debug("Message 2");
  // mpMON.Debug("Message 3");
  // mpMON.Debug("Message 4");
  // mpMON.Debug("Message 5");
  // mpMON.Debug("Message 6");
  // mpMON.Debug("Message 7");
  // mpMON.Debug("Message 8");
  // mpMON.Debug("Message 9");
  // mpMON.Debug("Message 10");
  // mpMON.Debug("Message 11");
  // mpMON.Debug("Message 12");
  // mpMON.Debug("Message 13");
  // mpMON.Debug("Message 14");
  // mpMON.Debug("Message 15");
  // mpMON.Debug("Message 16");
  // mpMON.Debug("Message 17");
  // mpMON.Debug("Message 18");
  // mpMON.Debug("Message 19");
  // mpMON.Debug("Message 20");
  // mpMON.Debug("Message 21");
  // mpMON.Debug("Message 22");
  // mpMON.Debug("Message 23");
  // mpMON.Debug("Message 24");
}

//===================================================================================================
// 
//===================================================================================================
void loop() {
  // put your main code here, to run repeatedly:

}
