#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <json-c/json.h>
#include "temp_sensor.h"

void getJSON(char *s[200]);

void main() {
    t0();
    char s[200];
    double temp;
    unsigned long t_last = 0;
    while (true)
    {
        getTemperature();
        if (millis() >= t_last + 10000)
        {
            t_last = millis();
            getJSON(&s);
            printf("%s",s);
        }   
    }
    return 0;
}

void getJSON(char *s[200]){
    char line[50];
    char oldest[30];
    char newest[30];
    stats tempStats;
    getOldestTime(&oldest);
    getNewestTime(&newest);
    tempStats = getTempStats();
    
    strcat(s,"{\n");
    strcat(s,"\t\"time\": {\n"); 
    sprintf(line, "\t\t\"start\": %s,\n",oldest); strcat(s,line);
    sprintf(line, "\t\t\"end\": %s\n",   newest); strcat(s,line);
    strcat(s,"\t},\n");
    sprintf(line, "\t\"min\": %.2f,\n",    tempStats.min); strcat(s,line);
    sprintf(line, "\t\"max\": %.2f,\n",    tempStats.max); strcat(s,line);
    sprintf(line, "\t\"average\": %.2f\n", tempStats.avg); strcat(s,line);
    strcat(s,"}\n");
}

