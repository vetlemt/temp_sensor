#define timevh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

unsigned long millis();
time_t t0();
void getUTC(char *pstr, unsigned long milli);
