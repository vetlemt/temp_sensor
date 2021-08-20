#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "readings.c"

int getTempRaw();
double getTemperature();
char readFile(char (*ca)[6][770]);
