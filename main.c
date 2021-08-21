#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <json-c/json.h>
#include "temp_sensor.h"


void main() {
    t0();
    double temp;
    unsigned long t_last = 0;
    stats statistics; 
    while (true)
    {
        temp = getTemperature();
        if (millis() >= t_last + 1000)
        {
            t_last = millis();

            statistics = getTempStats();
            printf("\nmax: %f\tmin: %f\tavg: %f",statistics.max,statistics.min,statistics.avg);
        }
        
    }

}

