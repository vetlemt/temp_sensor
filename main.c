#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "temp_sensor.c"

void main() {
    double temp;
    unsigned long t_last = 0;
    stats statistics; 
    while (true)
    {
        temp = getTemperature();
        if (millis() >= t_last + 1000)
        {
            printf("\nmillis time!");
            t_last = millis();
            printf("\ngetting max now!");

            statistics = getTempStats();
            printf("\nmax: %f\tmin: %f\tavg: %f",statistics.max,statistics.min,statistics.avg);
        }
        
    }
    return 0;

}