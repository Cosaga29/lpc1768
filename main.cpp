/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include <analyzer/Analyzer.hpp>

#define WAIT_TIME_MS 500

Analyzer *analyzer;

InterruptIn interuptPin(p6);
DigitalOut led(LED1);
DigitalOut clockPin(p5);

void onInterupt()
{
    analyzer->onClock();
}

void clockPins(int value)
{
    clockPin.write(value);
    led.write(value);
}

int main()
{
    printf("Logic Analyzer v%d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    analyzer = new Analyzer();
    interuptPin.rise(onInterupt);

    while (true)
    {
        clockPins(0);
        thread_sleep_for(500);
        clockPins(1);
        thread_sleep_for(500);
    }
}
