/*
 * This is the header file of the C++ OPP Library.
 * Tutorial: https://www.youtube.com/watch?v=mhYuiveM544
 * ALT + SHIFT + F >> Formate Code
 */

#pragma once         // ensures that the library is only copied in ONCE into the skecth.
#include <Arduino.h> // Inlude the Arduino lib.

// Simple library class to controll discrete LED´s.
class Aladim_LedController
{
public: // Declaration of functions: These are the "functions" exposed to the consumer of this library.

    // Constructor
    Aladim_LedController(int pPin);

    // Toggle the LED prototype
    void toggle();

    // Turn LED explizit ON prototype
    void turnOn();

    // Turn LED explizit OFF prototype
    void turnOff();

private: // Only visible from within this class
    // Variables of the class
    int pinLed;    // LED-Pin
    bool stateLed; // State of the LED
};