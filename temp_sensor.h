#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

unsigned long millis();
long getTempRaw();
double getTemperature();
char readFile(char (*ca)[6][770]);