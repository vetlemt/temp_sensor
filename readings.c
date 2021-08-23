#include "readings.h"

reading reads[1200] = {{0,0,false}}; 

// sore a new value in the readings array
void storeRead(reading temp){
    cleanReads();
    int i = 0;
    while (reads[i].used && i < 1200) { i++;}
    reads[i] = temp;
}

// mark all old readings as unused
void cleanReads(){

    unsigned long t = millis();
    long cutoff = t - 120000;
    if (cutoff >= 0)
    {
        for (int i = 0; i < 1200; i++)
        {
            if (reads[i].time < cutoff)
            {
                reads[i].used = false;
            }
        } 
    }

}
// get the max min and average from the last two minutes
stats getTempStats(){
    stats current;    
    current.max = getMaxTemp();
    current.min = getMinTemp();
    current.avg = getAvgTemp();
    return current;
}

// get the max temp from the last two minutes
double getMaxTemp(){
    double max = -100.0;
    cleanReads();

    for (int i = 0; i < 1200; i++)
    {
        if (reads[i].used == true)
        {
            max = max < reads[i].celsius ? reads[i].celsius : max; 
        }
    }
    
    return max;
}

// get the min temp from the last two minutes
double getMinTemp(){
    double min = 100.0;
    cleanReads(); 

    for (int i = 0; i < 1200; i++)
    {
        if (reads[i].used == true)
        {
            min = min > reads[i].celsius ? reads[i].celsius : min; 
        }
    }
    
    return min;
}

// get the average temp from the last two minutes
double getAvgTemp(){
    double avg = 0;
    cleanReads(); 

    int M = 0;
    for (size_t i = 0; i < 1200; i++)
    {
        if (reads[i].used == true)
        {
            avg += reads[i].celsius; 
            M++;
        }
    }
    if (M != 0)
    {
        avg = avg /(double)M; 
    }
    
    return avg;
}

void getOldestTime(char pstr[30]){
    unsigned long oldest = -1;
    cleanReads(); 

    for (int i = 0; i < 1200; i++)
    {
        if (reads[i].used == true)
        {
            oldest = oldest > reads[i].time ? reads[i].time : oldest; 
        }
    }
    getUTC(pstr,oldest);
}

void getNewestTime(char pstr[30]){
    unsigned long newest = 0;
    cleanReads(); 
    for (int i = 0; i < 1200; i++)
    {
        if (reads[i].used == true)
        {
            newest = newest < reads[i].time ? reads[i].time : newest; 
        }
    }
    getUTC(pstr,newest);
}
