#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "temp_sensor.h"
#include "transmission.h"

void main() {
    t0();
    char s[2000];
    char *ps;
    ps = s;
    char b[200];
    char *pb;
    pb = b;
    int response = 0;
    unsigned long t_last = 0;
    while (true)
    {
        getTemperature();
        if (millis() >= t_last + 120000)
        {
            t_last = millis();
            if (response != 500)
            {
                getJSON(pb);
            }
            response = post(pb,"/api/temperature");
            printf("\nresponse: %d\n",response);
            if (response == 500)
            {
                getJSONHistory(ps);
                int re2 = 0;
                while (re2 != 200)
                {
                    re2 = post(ps,"/api/temperature/missing");
                }
                
            }
            
            //printf("%s",ps);
        }   
    }
}

