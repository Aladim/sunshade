#include <Arduino.h>
#include "Aladim-Sunshade.h"
#include <Aladim-MotorDriver.h>
#include <Aladim_LedController.h>

// Create LED object for open sunshade operation
Aladim_LedController ledOpenSunshade(9); 

// Create LED object for the close sunshade operation
Aladim_LedController ledCloseSunshade(10);

// Create LED object for the stop motor operation
Aladim_LedController ledStopSunshade(11); 

// Create motot object
Aladim_MotorDriver motorDriver(5, 6);

// Default Constructor
Aladim_Sunshade::Aladim_Sunshade()
{
}

// Opens the sunshade
void Aladim_Sunshade::openSunshade()
{
    // Print
    Serial.print("open sunshade\n");

    // LED messages
    ledOpenSunshade.turnOn();
    ledCloseSunshade.turnOff();
    ledStopSunshade.turnOff();

    // Turn the motor clockwise (right)
    motorDriver.driveMotor(1);
}

// Closes the sunshade
void Aladim_Sunshade::closeSunshade()
{
    // Print
    Serial.print("closing sunshade\n");

    // LED messages
    ledOpenSunshade.turnOff();
    ledCloseSunshade.turnOn();
    ledStopSunshade.turnOff();

    // Turn the motor counterclockwise (left)
    motorDriver.driveMotor(2);
}

// Stops the motor
void Aladim_Sunshade::stopSunshade()
{
    // Print
    Serial.print("stop sunshade\n");

    // LED messages
    ledOpenSunshade.turnOff();
    ledCloseSunshade.turnOff();
    ledStopSunshade.turnOn();

    // Stop the motor
    motorDriver.motorStop();
}

// Turns on the warning light
void Aladim_Sunshade::warningLightOn()
{
    // Print
    Serial.print("turn on the warning light\n");
}

// Turns off the warning light
void Aladim_Sunshade::warningLightOff()
{
    // Print
    Serial.print("turn off the warning light\n");
}