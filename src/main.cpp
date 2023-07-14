// Include hardware
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
#include <Aladim-Sunshade.h>
// #include <LiquidCrystal.h>

/*
 * https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino
 * STOP using Serial.print in your Arduino code! THIS is better: https://www.youtube.com/watch?v=--KxxMaiwSE
 */

// IR reciver input pin  8
int IR_RECEIVE_PIN = 8;

// Create sunshade object
Aladim_Sunshade sunshade;

// Define operation mode
#define OperationMode 1

// Pin Number or the manual stop button
int stopButton = 7;

// Pin for clockwise PWM signal
int cwPwmPin = 5;

// Pin for counterclockwise PWM signal
int ccwPwmPin = 6;

// Stop Acceleration
void stopAcceleration(int pwmPin);

// Stop Motor
void stopMotor();

//

// Define a output methode for messages
#if OperationMode == 1
#define message(param) Serial.print(param)
#define messageln(param) Serial.println(param)
#else
#define message(param)
#define messageln(param)
#endif

// setup
void setup()
{
  // Start the serial monitor
  Serial.begin(9600);

  // Message - Just to know which program is running on my Arduino
  messageln(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Initialize the stop button pin as a input:
  pinMode(stopButton, INPUT_PULLUP);

  // Create IR receiver object
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

/*
 * The Main Loop
 */
void loop()
{

  // If stop button has event
  if (digitalRead(stopButton) == LOW)
  {
    // Invoke stopMotor
    stopMotor();
  }

  // If IR reciver
  if (IrReceiver.decode())
  {
    // Print complete received data in one line
    IrReceiver.printIRResultShort(&Serial);

    // Print the statement required to send this data
    IrReceiver.printIRSendUsage(&Serial);

    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      // Message
      messageln(F("Received noise or an unknown (or not yet enabled) protocol"));

      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }

    // Serial.println();

    /*
     * !!!Important!!! Enable receiving of the next value,
     * since receiving has stopped after the end of the current received data packet.
     */
    IrReceiver.resume();

    /*
     * Switch for the revieved IrReceiver data
     */
    switch (IrReceiver.decodedIRData.command)
    {

    // If button click 'ARROW UP' opens the sunschade
    case 0x18:

      // Invoke openSunshde
      sunshade.openSunshade();

      // Turn the motor clockwise (right)
      for (int i = 100; i < 200; i++)
      {
        if (i > 100)
        {
          // Write new value to output
          analogWrite(cwPwmPin, i);
        }

        // Message
        messageln((String) "Accelerate Motor: Direction of Rotation 'clockwise' PWM value: " + i);

        // If button click 'ASTERIX' stops the motor
        if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x16 || digitalRead(stopButton) == LOW)
        {
          // Invoke Stop Acceleration
          stopAcceleration(cwPwmPin);

          // Exit the 'for' loop
          break;
        }
        IrReceiver.resume();
      }

      // Message
      messageln((String) "Motor reached the maximum speed.");
      break;

    // If button click 'ARROW DOWN' closes the sunschade
    case 0x52:

      // Invoke closeSunshade
      sunshade.closeSunshade();

      // Turn the motor counterclockwise (left), increment current PWM value
      for (int i = 100; i < 200; i++)
      {
        if (i > 100)
        {
          // Write new value to output
          analogWrite(ccwPwmPin, i);
        }

        // Message
        messageln((String) "Accelerate Motor: Direction of Rotation 'counterclockwise' PWM value: " + i);

        // If button click 'ASTERIX' stops the motor
        if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x16 || digitalRead(stopButton) == LOW)
        {
          // Invoke Stop Acceleration
          stopAcceleration(ccwPwmPin);

          // Break loop
          break;
        }
        IrReceiver.resume();
      }
      // Message
      messageln((String) "Motor reached the maximum speed.");
      break;

    // If button click 'ASTERIX' stops the motor
    case 0x16:
      stopMotor();
      break;

    // If button click 'ASTERIX' turn on the warning light
    case 0x5A:
      // Invoke warningLightOn
      sunshade.warningLightOn();
      break;

    // If button click 'HASHTAG' turn off the warning light
    case 0xD:
      // invoke warningLightOff
      sunshade.warningLightOff();
      break;
    default:
      break;
    }

    /*
     * !!!Important!!! Enable receiving of the next value,
     * since receiving has stopped after the end of the current received data packet.
     */
    IrReceiver.resume();
  }
}

/*
 * Helper Methods
 */

// Stop the motor
void stopMotor()
{

  // Message
  messageln("Stop the motor\n");

  // Invoke stopMotor
  sunshade.stopSunshade();

  // Write new value to output
  analogWrite(cwPwmPin, 0);

  // Write new value to output
  analogWrite(ccwPwmPin, 0);
}

// Stop Acceleration
void stopAcceleration(int pwmPin)
{
  // Message
  messageln((String) "Accelerate Motor was stop!");

  // Write new value to output
  analogWrite(ccwPwmPin, 0);

  // Invoke stopSunshade
  sunshade.stopSunshade();

  // delay(3000);
}