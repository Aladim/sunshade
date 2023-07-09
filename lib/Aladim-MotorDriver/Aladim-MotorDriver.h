/*
 * This is the header file of the C++ OPP Library.
 */

#pragma once         // ensures that the library is only copied in ONCE into the skecth.
#include <Arduino.h> // Inlude the Arduino lib.

//#define DECODE_NEC
//#include <IRremote.hpp>

// Simple library class to controll the a dc motor via a h-bridge modul
class Aladim_MotorDriver
{
public: // Declaration of functions: These are the "functions" exposed to the consumer of this library.
    // Constructor
    Aladim_MotorDriver(int rpwmPin, int lpwmPin);

    // Drives the motor. The parameter directionOfRotation has the value range '1' or '2' and turns the motor 'clockwise' (right) or 'counterclockwise' (left)
    void driveMotor(int directionOfRotation);

    // Motor stop
    void motorStop();

private: // Only visible from within this class


    // int IR_RECEIVE_PIN; // IR reciver input pin  8

    // Variables of the class
    int RPWM_Output; // Arduino PWM output pin > connect to IBT-2 pin 1 (RPWM)
    int LPWM_Output; // Arduino PWM output pin > connect to IBT-2 pin 2 (LPWM)

    int PWM_Output; // Arduino PWM output pin > dynamic

    // Current rotation value
    int CurrentPWM;

    // Maximum rotation value
    int MaximumPWM;

    // Minimum rotation value
    int MinimumPWM;

    // Accelerate the motor
    void accelerateMotor(int PWM_Output, int directionOfRotation);

    // Deive the motor
    void driveMotor(int pWM_Output, int currentPWM, int directionOfRotation);
};