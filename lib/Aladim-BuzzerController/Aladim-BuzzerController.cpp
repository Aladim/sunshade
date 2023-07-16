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
Toggle the Buzzer:
The line negates the logical value of the stateLed attribute.
If stateLed was true at first, it is false afterwards.
If the status of the LED is then updated with the command, the LED changes its status each time the method is called.
*/
void Aladim_BuzzerController::toggle()
{
    stateBuzzer = !stateBuzzer;
    digitalWrite(pinBuzzer, stateBuzzer);
}

/**
 * Turn Buzzer ON
 */
void Aladim_BuzzerController::turnOn()
{
    digitalWrite(pinBuzzer, HIGH);
    digitalWrite(pinBuzzer, HIGH);
}

/**
 * Turn Buzzer OFF
 */
void Aladim_BuzzerController::turnOff()
{
    digitalWrite(pinBuzzer, LOW);
}

/**
 * Buzzer Beep
 */
void Aladim_BuzzerController::beep()
{
    digitalWrite(pinBuzzer, HIGH);
    delay(500);
    digitalWrite(pinBuzzer, LOW);
}
