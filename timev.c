#include "timev.h"

unsigned long millis()
{
    unsigned long milli = clock() / (1000);
    return milli;
}

time_t t0()
{
    static time_t t_0;
    static unsigned long milli_0;
    static bool stored = false;
    if (!stored)
    {
        t_0 = time(NULL);
        milli_0 = millis();
        printf("t_0: %ld\tmilli_0: %ld\n", t_0, milli_0);
        stored = true;
    }
    return t_0;
}

void getUTC(char *pstr, unsigned long milli)
{
    time_t t;
    struct tm *ptm;
    t = t0();
    t = t + (milli / 1000);
    ptm = gmtime(&t);

    sprintf(pstr, "20%02d-%02d-%02dT%02d:%02d:%02d.0000000Z", ptm->tm_year % 100,
            ptm->tm_mon + 1,
            ptm->tm_mday,
            ptm->tm_hour,
            ptm->tm_min,
            ptm->tm_sec);
}
