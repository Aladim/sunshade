/*
 * This is the header file of the C++ OPP Library.
 */

#pragma once         // ensures that the library is only copied in ONCE into the skecth.
#include <Arduino.h> // Inlude the Arduino lib.

// Simple library class to controll the a dc motor via a h-bridge modul
class Aladim_MotorDriver
{
public: // Declaration of functions: These are the "functions" exposed to the consumer of this library.
    // Constructor
    Aladim_MotorDriver(int rpwmPin, int lpwmPin);

    // Motor turn clockwise (right)
    void motorClockwise();

    // Motor turn counterclockwise (left)
    void mototCounterclockwise();

    // Motor stop
    void motorStop();

private: // Only visible from within this class
    // Variables of the class
    int RPWM_Output; // Arduino PWM output pin > connect to IBT-2 pin 1 (RPWM)
    int LPWM_Output; // Arduino PWM output pin > connect to IBT-2 pin 2 (LPWM)

    // Current rotation value
    int CurrentPWM;

    // Maximum rotation value
    int MaximumPWM;

    // Minimum rotation value
    int MinimumPWM;

    // Accelerate the motor
    void accelerateMotor();

    // Slow down the motor
    void slowdownMotor();
};