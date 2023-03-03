#ifndef LOGIC_ANALYZER
#define LOGIC_ANALYZER

#include "mbed.h"

struct Analyzer
{
    BusIn mBus;

    Analyzer() : mBus(p13, p14, p15, p16, p17, p18, p19, p20)
    {
        mBus.mode(PullNone);
    }

    void onClock()
    {
        printf("%X\n", mBus.read());
    }
};

#endif