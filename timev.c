#include "timev.h"

unsigned long millis(){
    unsigned long milli = clock()/(1000);   
    return milli;
}

time_t t0(){
    static time_t t_0;
    static unsigned long milli_0;
    static bool stored = false;
    if (!stored)
    {
        t_0 = time(NULL);
        milli_0 = millis();
        printf("t_0: %ld\tmilli_0: %ld",t_0,milli_0);
        stored = true;
        }
    return t_0;
}