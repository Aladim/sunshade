#include <Arduino.h>
#include "Aladim_LedController.h"

    // Default Constructor
    Aladim_LedController::Aladim_LedController(int pPin)
    {
        pinLed = pPin;           // Attribute 'pinLed' recieves the pin number value of the constructor
        stateLed = false;        // State of the LED is false (LOW)
        pinMode(pinLed, OUTPUT); // Set the pin number as OUTPUT
    }

    /*
    Toggle the LED:
    The line negates the logical value of the stateLed attribute.
    If stateLed was true at first, it is false afterwards.
    If the status of the LED is then updated with the command, the LED changes its status each time the method is called.
    */
    void Aladim_LedController::toggle()
    {

        stateLed = !stateLed;
        digitalWrite(pinLed, stateLed);
    }

    /**
     * Turn LED explizit ON
     */
    void Aladim_LedController::turnOn()
    {
        digitalWrite(pinLed, HIGH);
    }

    /**
     * Turn LED explizit OFF
     */
    void Aladim_LedController::turnOff()
    {
        digitalWrite(pinLed, LOW);
    }

