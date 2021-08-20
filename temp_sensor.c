#include "temp_sensor.h"

double getTemperature(){
    const int resolution = 12;      // bits
    const int N = 1 << resolution;  // number of steps 
    const double alpha = 100 / (double)N; // step size, (sensor range)/steps
    const int t_delta = 100;        // min time between reads
    static unsigned long t_last = 0;
    double temp_c;
    if ( millis() >= t_last + t_delta)
    {
        t_last = millis();
        long temp_raw = getTempRaw();
        temp_c = temp_raw * alpha - 50;  // convert raw sensor data to celsius

        printf("\ntemp in C:%f \n", temp_c);
    }
    return temp_c;
}

long getTempRaw(){
    static int count = 0;
    char c[6];
    char ca[6][770];
    FILE *fptr;

    if ((fptr = fopen("temperature.txt", "r")) == NULL) {
        printf("Error! File cannot be opened.");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    // reads all lines of temperature.txt and writes them to ca
    int j = 0;
    while (fgets(c, sizeof(c), fptr))
    {
        for (size_t i = 0; i < 6; i++)
        {
            ca[i][j] = c[i];
        }
        j++;

    }
    fclose(fptr);

    char cc[6];
    for (size_t i = 0; i < 6; i++)
        {
            cc[i] = ca[i][count];
        }   

    count = count >= 766 ? 0 : count + 1;   // loops the readings 

    char *ptr;
    int ret = strtol(cc, &ptr,10);
     printf("\nData from the file: %d  mesurement number: %d", ret,count);

    return ret; 
}

char readFile(char readings){
    
}

double maxTemperature(){
return 0;
}

double minTemperature(){
return 0;
}

double avgTemperature(){
return 0;
}

unsigned long millis(){
    unsigned long milli = clock()/(1000);   
    return milli;
}

