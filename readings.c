#include "readings.h"

unsigned long millis(){
    unsigned long milli = clock()/(1000);   
    return milli;
}

// get a pointer to the array of sensor readings from the last two minutes
void* getReadings(){
    static reading readings[1200] = {{0,0,false}};  // create sensor readings array
    reading (*ptr)[1200];       // create a pointer for the arrray
    ptr = &readings;
    return ptr; 
}

// sore a new value in the readings array
void storeRead(reading temp){
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads();
    int i = 0;
    while ((*reads)[i].used == true) { i++;}
    (*reads)[i] = temp;
    printf("\ntemp stored!");
}

// mark all old readings as unused
void cleanReads(){
    reading (*reads)[1200];
    reads = getReadings();
    unsigned long t = millis();
    for (size_t i = 0; i < 1200; i++)
    {
        if ((*reads)[i].time > t + 1200000)
        {
            (*reads)[i].used = false;
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
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads();

    for (int i = 0; i < 1200; i++)
    {
        if ((*reads)[i].used == true)
        {
            max = max < (*reads)[i].celsius ? (*reads)[i].celsius : max; 
        }
    }
    
    return max;
}

// get the min temp from the last two minutes
double getMinTemp(){
    double min = 100.0;
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads(); 

    for (int i = 0; i < 1200; i++)
    {
        if ((*reads)[i].used == true)
        {
            min = min > (*reads)[i].celsius ? (*reads)[i].celsius : min; 
        }
    }
    
    return min;
}

// get the average temp from the last two minutes
double getAvgTemp(){
    double avg = 0;
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads(); 

    int M = 0;
    for (size_t i = 0; i < 1200; i++)
    {
        if ((*reads)[i].used == true)
        {
            avg += (*reads)[i].celsius; 
            M++;
        }
    }
    if (M != 0)
    {
        avg = avg /(double)M; 
    }
    
    return avg;
}
