#include <Arduino.h>
#include "Aladim-MotorDriver.h"

// Default Constructor
Aladim_MotorDriver::Aladim_MotorDriver(int rpwmPin, int lpwmPin)
{
    // IR reciver input pin  8
    // IR_RECEIVE_PIN = 8;

    // Create IR receiver object
    // IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    RPWM_Output = rpwmPin; // Arduino PWM output > connect to IBT-2 pin 1 (RPWM)
    LPWM_Output = lpwmPin; // Arduino PWM output > connect to IBT-2 pin 2 (LPWM)

    pinMode(RPWM_Output, OUTPUT); // Set the pin number as OUTPUT
    pinMode(LPWM_Output, OUTPUT); // Set the pin number as OUTPUT

    CurrentPWM = 0;   // Current rotation value starts with '0'
    MaximumPWM = 255; // Maximum rotation value
    MinimumPWM = 0;   // Minimum rotation value
}

/*
 * Turn the motor clockwise (right) or counterclockwise (left)
 */
void Aladim_MotorDriver::driveMotor(int directionOfRotation)
{

    // Switch direction of rotation
    switch (directionOfRotation)
    {
    case 1:
        // Print
        Serial.println((String) "Direction of Rotation: " + directionOfRotation + " Turn the motor clockwise.");

        // Accelerate motor
        analogWrite(LPWM_Output, 0);
        accelerateMotor(RPWM_Output, directionOfRotation);

        break;
    case 2:
        // Print
        Serial.println((String) "Direction of Rotation: " + directionOfRotation + " Turn the motor clockwise.");

        // Accelerate motor
        analogWrite(RPWM_Output, 0);
        accelerateMotor(LPWM_Output, directionOfRotation);

        break;
    default:
        // Print
        Serial.println((String) "Direction of Rotation: " + directionOfRotation + " Stop the motor.");

        break; // Wird nicht benötigt, wenn Statement(s) vorhanden sind
    }
}

/*
 * Accelerate the motor
 */
void Aladim_MotorDriver::accelerateMotor(int PWM_Output, int directionOfRotation)
{

    // IrReceiver.resume();

    // Increment current PWM value
    for (int i = CurrentPWM; i < MaximumPWM; i++)
    {
        // Increase current PWM
        CurrentPWM++;

        // Write new value to output
        analogWrite(PWM_Output, CurrentPWM);

        // Print
        Serial.println((String) "Accelerate Motor: Direction of Rotation: " + directionOfRotation + " PWM value: " + CurrentPWM);

        /*if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x19)
        {
            Serial.println((String) "Accelerate Motor was stop!");

            IrReceiver.resume();
            break; // Exit the 'for' loop
        }
        */
    }

    driveMotor(PWM_Output, CurrentPWM, directionOfRotation);
}

/**
 * Drive the motor
 */
        void Aladim_MotorDriver::driveMotor(int pWM_Output, int currentPWM, int directionOfRotation)
        {

            // Write new value to output
            analogWrite(pWM_Output, currentPWM);

            // Print
            Serial.println((String) "Drive Motor: Direction of Rotation: " + directionOfRotation + " PWM value: " + currentPWM);

            // Motor rotates for specific delay time
            delay(10000);

            // Stop the motor
            motorStop();
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