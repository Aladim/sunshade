/*
 * This is the header file of the C++ OPP Library.
 */

#pragma once         // Ensures that the library is only copied in ONCE into the skecth.
#include <Arduino.h> // Inlude the Arduino lib.

// Simple library class to controll discrete LED´s.
class Aladim_BuzzerController
{
public: // Declaration of functions: These are the "functions" exposed to the consumer of this library.

    // Constructor
    Aladim_BuzzerController(int pPin);

    // Toggle Buzzer
    void toggle();

    // Buzzer On
    void turnOn();

    // Buzzer Off
    void turnOff();

    // Buzzer Beep
    void beep();

private: // Only visible from within this class
    // Variables of the class
    int pinBuzzer;    // Buzzer Pin
    bool stateBuzzer; // State of the LED
};