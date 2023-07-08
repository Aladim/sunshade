#include <Arduino.h>
#include "Aladim-MotorDriver.h"

// Default Constructor
Aladim_MotorDriver::Aladim_MotorDriver(int rpwmPin, int lpwmPin)
{
    RPWM_Output = rpwmPin; // Arduino PWM output > connect to IBT-2 pin 1 (RPWM)
    LPWM_Output = lpwmPin; // Arduino PWM output > connect to IBT-2 pin 2 (LPWM)

    pinMode(RPWM_Output, OUTPUT); // Set the pin number as OUTPUT
    pinMode(LPWM_Output, OUTPUT); // Set the pin number as OUTPUT

    CurrentPWM = 0;   // Current rotation value starts with '0'
    MaximumPWM = 255; // Maximum rotation value
    MinimumPWM = 0; // Minimum rotation value
}

/*
 * Turn the motor clockwise (right)
 */
void Aladim_MotorDriver::motorClockwise()
{
    // Print
    Serial.print("Turn the motor clocwise\n");

    // Motor
    analogWrite(LPWM_Output, 0);
    accelerateMotor();
}

/**
 * Turn the motor counterclockwise (left)
 */
void Aladim_MotorDriver::mototCounterclockwise()
{

    // Print
    Serial.print("Turn the motor counterclocwise\n");

    // Motor
    analogWrite(RPWM_Output, 0);
    slowdownMotor();
}

/**
 * Stop the motor
 */
void Aladim_MotorDriver::motorStop()
{
    // Print
    Serial.print("Stop the motor\n");

    // Motor
    CurrentPWM = 0;
    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, 0);
}

/*
 * Accelerate the motor
 */
void Aladim_MotorDriver::accelerateMotor()
{
    // Increase current PWM value
    for (CurrentPWM; CurrentPWM < MaximumPWM + 1; CurrentPWM++)
    {

        // Write new value to output
        analogWrite(RPWM_Output, CurrentPWM);

        // Print
        Serial.println((String) "Max rotation value: " + CurrentPWM);
    }
}

/*
 * Slow down the motor
 */
void Aladim_MotorDriver::slowdownMotor()
{
    for (CurrentPWM; CurrentPWM > MinimumPWM; CurrentPWM--)
    {

        Serial.print("Komm ich überhautpt in den Loop");

        // Write new value to output
        analogWrite(LPWM_Output, CurrentPWM);

        // Print
        Serial.println((String) "Max rotation value: " + CurrentPWM);
    }
}