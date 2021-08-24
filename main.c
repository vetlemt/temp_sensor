#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "temp_sensor.h"
#include "transmission.h"

void main()
{
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
        if (millis() >= t_last + 120000) //every two minutes
        {
            t_last = millis();
            if (response != 500) // if there wasn't a server error
            {
                getJSON(pb);
            }
            response = post(pb, "/api/temperature");
            printf("\nresponse: %d\n", response);
            if (response == 500) // if there is a server error
            {
                getJSONHistory(ps);
                int re2 = 0;
                while (re2 != 200) // post until no server error
                {
                    re2 = post(ps, "/api/temperature/missing");
                }
            }
        }
    }
}
