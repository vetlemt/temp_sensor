#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <json-c/json.h>
#include "temp_sensor.h"


void main() {
    t0();
    char s[50];
    getUTC(&s,0);
    printf("\n%s\n",s);
    getUTC(&s,1000);
    printf("%s\n",s);

    double temp;
    unsigned long t_last = 0;
    stats statistics; 
    while (true)
    {
        temp = getTemperature();
        if (millis() >= t_last + 10000)
        {
            t_last = millis();
            getOldestTime(&s);
            printf("%s\n",s);
            getNewestTime(&s);
            printf("%s\n",s);
            statistics = getTempStats();
            printf("\nmax: %f\tmin: %f\tavg: %f",statistics.max,statistics.min,statistics.avg);
        }
        
    }
    return 0;
}

