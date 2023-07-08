#include <Arduino.h>
#include "Aladim-Sunshade.h"
#include <Aladim-MotorDriver.h>

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

    // Turn the motor clockwise (right)
    motorDriver.motorClockwise();
}

// Closes the sunshade
void Aladim_Sunshade::closeSunshade()
{
    // Print
    Serial.print("closing sunshade\n");

    // Turn the motor counterclockwise (left)
    motorDriver.mototCounterclockwise();
}

// Stops the motor
void Aladim_Sunshade::stopSunshade()
{
    // Print
    Serial.print("stop sunshade\n");

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