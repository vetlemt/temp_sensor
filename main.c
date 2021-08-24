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
    char s[2000];
    char *ps;
    ps = s;
    int response;
    unsigned long t_last = 0;
    while (true)
    {
        getTemperature();
        if (millis() >= t_last + 1000)
        {
            t_last = millis();
            getJSON(ps);
            //printf("%s",s);
            response = post(s,"/api/temperature");
            printf("\nresponse: %d\n",response);
            getJSONHistory(ps);
            //printf("%s",ps);
        }   
    }
}

