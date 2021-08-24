#define temp_sensorh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef readingsh
#include "readings.h"
#endif

#ifndef timevh
#include "timev.h"
#endif

unsigned long millis();
int getTempRaw();
double getTemperature();
char readFile(char (*ca)[6][770]);
