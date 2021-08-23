#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <json-c/json.h>

#include "temp_sensor.h"
#include "transmission.h"

void main() {
    t0();
    char s[200];
    unsigned long t_last = 0;
    while (true)
    {
        getTemperature();
        if (millis() >= t_last + 1000)
        {
            t_last = millis();
            getJSON(s);
            //printf("%s",s);
            post(s,"/api/temperature");
        }   
    }
}

