#define readingsh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef timevh
    #include "timev.h"
#endif
typedef struct
{
    double celsius;
    unsigned long time;
    bool used;
}reading;

typedef struct
{
    double max;
    double min;
    double avg;
}stats;


void* getReadings();
void storeRead(reading temp);
void cleanReads();
stats getTempStats();
double getMaxTemp();
double getMinTemp();
double getAvgTemp();
void getOldestTime(char *pstr);
void getNewestTime(char *pstr);
