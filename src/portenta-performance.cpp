#include "portenta-performance.h"
#include "portenta-monitor.h"

//===================================================================================================
// HEAP PERFORMANCE
//===================================================================================================
void Performance::HeapPerformance(void) {
    mbed_stats_heap_t heap_stats;

    mpMON.Debug("[Heap stats]");

    mbed_stats_heap_get(&heap_stats);
    
    mpMON.Debug(
        String("Current heap: ")+heap_stats.current_size+
        String(" Max heap size: ")+heap_stats.max_size
    );

    mpMON.Debug(String("Allocating 1000 bytes"));
    
    void *allocation = malloc(1000);
    mbed_stats_heap_get(&heap_stats);

    mpMON.Debug(
        String("Post-Alloc; Current heap: ")+heap_stats.current_size+
        String(" Post-Alloc; Max heap size: ")+heap_stats.max_size
    );

    free(allocation);

    mpMON.Debug(String("Freed 1000 bytes"));

    mbed_stats_heap_get(&heap_stats);

    mpMON.Debug(
        String("Post-Free; Current heap: ")+heap_stats.current_size+
        String(" Post-Free; Max heap size: ")+heap_stats.max_size
    );
    mpMON.Debug(String());
}

//===================================================================================================
// STACK PERFORMANCE
//===================================================================================================
void Performance::StackPerformance(void)
{
    mpMON.Debug(String("[Stack stats]"));

    int cnt = osThreadGetCount();
    mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));

    cnt = mbed_stats_stack_get_each(stats, cnt);
    for (int i = 0; i < cnt; i++) {
        mpMON.Debug(
            String("Thread: 0x")+stats[i].thread_id+
            String(" Stack size: ")+stats[i].reserved_size+
            String(" Max stack: ")+stats[i].max_size
        );             
    }
    mpMON.Debug(String());
}

//===================================================================================================
// CPU PERFORMANCE
//===================================================================================================
void Performance::CpuPerformance(void) {
    mbed_stats_cpu_t stats;
    
    mpMON.Debug(String("[CPU stats]"));

    mbed_stats_cpu_get(&stats);

    mpMON.Debug(
        String("Uptime: ")+(unsigned long int)(stats.uptime / 1000)+
        String( " Sleep time: ")+(unsigned long int)(stats.sleep_time / 1000)+
        String(" Deep Sleep: ")+(unsigned long int)(stats.deep_sleep_time / 1000)
    );

    mpMON.Debug(String());
}

//===================================================================================================
// RUN WORKER THREAD ON DEMAND, NO SAFETY DUPLICATE.
//===================================================================================================
void Performance::Run(void) {
    runit = true;    
    Performance_worker.start(callback(Run_callback));
}

//===================================================================================================
// SINGLETON
//===================================================================================================
Performance &Performance::getInstance() {
  static Performance instance;
  return instance;
}

Performance &mpPERF = mpPERF.getInstance();

//===================================================================================================
// WORKER
//===================================================================================================
void Performance::Run_callback() {
    while (mpPERF.runit)
    {
        mpMON.HoldItForWhile(true);
        mpPERF.CpuPerformance();
        mpPERF.StackPerformance();
        mpPERF.HeapPerformance();  
        mpMON.HoldItForWhile(false);  
        
        #if MBED_MAJOR_VERSION == 2
            wait_ms(mpPERF.pause);
        #elif MBED_MAJOR_VERSION == 5
            thread_sleep_for(mpPERF.pause);
        #else
            ThisThread::sleep_for(mpPERF.pause);
        #endif
    }
    
}