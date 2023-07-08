#include <Arduino.h>
#include "Aladim-Sunshade.h"
#include <Aladim_LedController.h>
#include <Aladim-MotorDriver.h>

// Create LED object for open sunshade operation
Aladim_LedController ledOpenSunshade(9);

// Create LED object for the close sunshade operation
Aladim_LedController ledCloseSunshade(10);

// Create LED object for the stop motor operation
Aladim_LedController ledStopMotor(11);

// Create motot object
Aladim_MotorDriver motorDriver(5,6);

// Default Constructor
Aladim_Sunshade::Aladim_Sunshade()
{
}

// Opens the sunshade
void Aladim_Sunshade::openSunshade()
{
    // Print
    Serial.print("open sunshade\n");

    // Turn on ledOpenSunshade
    ledOpenSunshade.turnOn();

    // Turn the motor clockwise (right)
    motorDriver.motorClockwise();

    // set delay
    delay(3000);

    // Trun off ledOpenSunshade
    ledOpenSunshade.turnOff();
}

// Closes the sunshade
void Aladim_Sunshade::closeSunshade()
{
    // Print
    Serial.print("closing sunshade\n");

    // Turn on ledCloseSunshade
    ledCloseSunshade.turnOn();

    // Turn the motor counterclockwise (left)
    motorDriver.mototCounterclockwise();

    // set delay
    delay(3000);

    // Trun off ledCloseSunshade
    ledCloseSunshade.turnOff();
}

// Stops the motor
void Aladim_Sunshade::stopSunshade()
{
    // Print
    Serial.print("stop sunshade\n");

    // Turn on ledStopMotor
    ledStopMotor.turnOn();

    // Stop the motor
    motorDriver.motorStop();

    // set delay
    delay(3000);

    // Trun off ledStopMotor
    ledStopMotor.turnOff();
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