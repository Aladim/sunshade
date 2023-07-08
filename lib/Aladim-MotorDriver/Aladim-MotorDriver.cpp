#include <Arduino.h>
#include "Aladim-MotorDriver.h"

// Default Constructor
Aladim_MotorDriver::Aladim_MotorDriver(int rpwmPin, int lpwmPin)
{
    RPWM_Output = rpwmPin; // Arduino PWM output > connect to IBT-2 pin 1 (RPWM)
    LPWM_Output = lpwmPin; // Arduino PWM output > connect to IBT-2 pin 2 (LPWM)

    pinMode(RPWM_Output, OUTPUT); // Set the pin number as OUTPUT
    pinMode(LPWM_Output, OUTPUT); // Set the pin number as OUTPUT
}

/*
 * Turn the motor clockwise (right)
 */
void Aladim_MotorDriver::motorClockwise()
{
    // Print
    Serial.print("Turn the motor clocwise\n");

    // reverse rotation
    int reversePWM = 200; 

    // Motor
    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, reversePWM);
}

/**
 * Turn the motor counterclockwise (left)
 */
void Aladim_MotorDriver::mototCounterclockwise()
{

    // Print
    Serial.print("Turn the motor clocwise\n");

    // forward rotation
    int forwardPWM = 200; 

    // Motor
    analogWrite(LPWM_Output, forwardPWM);
    analogWrite(RPWM_Output, 0);
}

/**
 * Stop the motor
 */
void Aladim_MotorDriver::motorStop()
{
    // Print
    Serial.print("Stop the motor\n");

    // Motor
    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, 0);
}
