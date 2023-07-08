/*
 * This is the header file of the C++ OPP Library.
 * ALT + SHIFT + F >> Formate Code
 */

#pragma once                      // ensures that the library is only copied in ONCE into the skecth
#include <Arduino.h>              // Inlude the Arduino lib

// Simple library class to controll the sunshade
class Aladim_Sunshade
{
public: // Declaration of functions: These are the "functions" exposed to the consumer of this library
    // Constructor
    Aladim_Sunshade();

    // Opens the sunshade
    void openSunshade();

    // Close the sunshade
    void closeSunshade();

    // Stops the motor
    void stopSunshade();

    // Turns on the warning light
    void warningLightOn();

    // Turns off the warning light
    void warningLightOff();

private: // Only visible from within this class
         // Variables of the class
         // int pinLed;    // LED-Pin
         // bool stateLed; // State of the LED
};