#include "temp_sensor.h"

double getTemperature(){
    const int resolution = 12;      // bits
    const int N = (1 << resolution) - 1 ; // number of steps 
    const double alpha = 100 / (double)N; // step size, (sensor range)/steps
    const int t_delta = 100;        // min time between reads
    static unsigned long t_last = 0;// the last time the temp was read
    reading temp = {0,0,false};
    
    if ( millis() >= t_last + t_delta)  // if the minimum time period has elapsed
    {
        t_last = millis();
        int temp_raw = getTempRaw();
        temp.celsius = temp_raw * alpha - 50;  // convert raw sensor data to celsius
        temp.time = millis();
        temp.used = true;
        storeRead(temp);

        printf("\ntemp in C:%f \n", temp.celsius);
    }
    

    return temp.celsius;
}

int getTempRaw(){
    static int count = 0;
    static char ca[6][770];
    
    // read the file once and store it in ca
    static bool read = false;
    if (read == false)
    {
        char (*cptr)[6][770];
        cptr = &ca;
        readFile(cptr);
        read = true;
    }
    
    // copy the current reading to cc
    char cc[6];
    for (size_t i = 0; i < 6; i++)
        {
            cc[i] = ca[i][count];
        }   

    count = count >= 766 ? 0 : count + 1;   // loops the readings 

    // parse the number string into int
    char *ptr;
    int ret = strtol(cc, &ptr,10);
     printf("\nData from the file: %d  mesurement number: %d", ret,count);

    return ret; 
}

char readFile(char (*ca)[6][770]){
    char c[6];
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
            (*ca)[i][j] = c[i];
        }
        j++;

    }
    fclose(fptr);
    return '0';
}

unsigned long millis(){
    unsigned long milli = clock()/(1000);   
    return milli;
}

void* getReadings(){
    static reading readings[1200] = {{0,0,false}};
    reading (*ptr)[1200];
    ptr = &readings;
    return ptr;
}

void storeRead(reading temp){
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads();
    int i = 0;
    while ((*reads)[i].used == true) { i++;}
    (*reads)[i] = temp;
    printf("\ntemp stored!");
}

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

stats getTempStats(){
    stats current;    
    current.max = getMaxTemp();
    current.min = getMinTemp();
    current.avg = getAvgTemp();
    return current;
}


double getMaxTemp(){
    double max = -100.0;
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads(); // do i really need it?

    for (int i = 0; i < 1200; i++)
    {
        if ((*reads)[i].used == true)
        {
            max = max < (*reads)[i].celsius ? (*reads)[i].celsius : max; 
        }
    }
    
    return max;
}

double getMinTemp(){
    double min = 100.0;
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads(); // do i really need it?

    for (int i = 0; i < 1200; i++)
    {
        if ((*reads)[i].used == true)
        {
            min = min > (*reads)[i].celsius ? (*reads)[i].celsius : min; 
        }
    }
    
    return min;
}

double getAvgTemp(){
    double avg = 0;
    reading (*reads)[1200];
    reads = getReadings();
    cleanReads(); // do i really need it?

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
