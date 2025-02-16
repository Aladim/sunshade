#include <Arduino.h>
#include "Aladim-Sunshade.h"
#include <Aladim_LedController.h>

// Create LED object for open sunshade operation
Aladim_LedController ledOpenSunshade(6);

// Create LED object for the close sunshade operation
Aladim_LedController ledCloseSunshade(10);

// Create LED object for the stop motor operation
Aladim_LedController ledStopSunshade(11);

// Default Constructor
Aladim_Sunshade::Aladim_Sunshade()
{
}

// Opens the sunshade
void Aladim_Sunshade::openSunshade()
{
    // LED switch
    ledOpenSunshade.turnOn();
    ledCloseSunshade.turnOff();
    ledStopSunshade.turnOff();
}

// Closes the sunshade
void Aladim_Sunshade::closeSunshade()
{
    // LED switch
    ledOpenSunshade.turnOff();
    ledCloseSunshade.turnOn();
    ledStopSunshade.turnOff();
}

// Stops the motor
void Aladim_Sunshade::stopSunshade()
{
    // LED switch
    ledOpenSunshade.turnOff();
    ledCloseSunshade.turnOff();
    ledStopSunshade.turnOn();
}

// Turns on the warning light
void Aladim_Sunshade::warningLightOn()
{

}

// Turns off the warning light
void Aladim_Sunshade::warningLightOff()
{

}