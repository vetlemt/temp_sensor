#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

unsigned long millis();
int getTempRaw();
double getTemperature();
char readFile(char (*ca)[6][770]);
void* getReadings();
void storeRead(reading temp);
void cleanReads();
stats getTempStats();
double getMaxTemp();
double getMinTemp();
double getAvgTemp();
