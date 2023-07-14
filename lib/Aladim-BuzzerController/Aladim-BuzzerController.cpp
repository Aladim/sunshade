#include <Arduino.h>
#include "Aladim-BuzzerController.h"

    // Default Constructor
    Aladim_BuzzerController::Aladim_BuzzerController(int pPin)
    {
        pinBuzzer = pPin;           // Attribute 'pinLed' recieves the pin number value of the constructor
        stateBuzzer = false;        // State of the LED is false (LOW)
        pinMode(pinBuzzer, OUTPUT); // Set the pin number as OUTPUT
    }

    /*
    Toggle the LED:
    The line negates the logical value of the stateLed attribute.
    If stateLed was true at first, it is false afterwards.
    If the status of the LED is then updated with the command, the LED changes its status each time the method is called.
    */
    void Aladim_BuzzerController::toggle()
    {
        stateBuzzer = !stateBuzzer;
        digitalWrite(pinBuzzer, stateBuzzer);
    }
