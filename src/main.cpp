// Include hardware
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
#include <Aladim-Sunshade.h>
#include <Aladim-BuzzerController.h>
// #include <LiquidCrystal.h>

/*
 * https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino
 * STOP using Serial.print in your Arduino code! THIS is better: https://www.youtube.com/watch?v=--KxxMaiwSE
 */

// IR reciver input pin  8
int IR_RECEIVE_PIN = 8;

// Create sunshade object
Aladim_Sunshade sunshade;

// Create buzzer object
Aladim_BuzzerController buzzer(12);

// Define operation mode
#define OperationMode 1

// Pin Number for the manual stop button
int stopButton = 7;

// Pin Number for the manual open sunshade
int openButton = 4;

// Pin Number for the manual close sunshade
int closeButton = 2;

// Pin for clockwise PWM signal
int cwPwmPin = 5;

// Pin for counterclockwise PWM signal
int ccwPwmPin = 6;

// Puls Power Modulation Minimum
int ppwMin = 100;

// Puls Power Modultion Maximum
int ppwMax = 200;

// Stop Acceleration
void stopAcceleration(int pwmPin);

// Stop Acceleration
void startAcceleration(int pwmPin);

// Stop Motor
void stopMotor();

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

  // Initialize the stop button pin input
  pinMode(stopButton, INPUT_PULLUP);

  // Initialize the open button pin input
  pinMode(openButton, INPUT_PULLUP);

  // Initialize the close button pin input
  pinMode(closeButton, INPUT_PULLUP);

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

  // If open button has event
  if (digitalRead(openButton) == LOW)
  {
    // Invoke startAcceleration
    startAcceleration(cwPwmPin);
  }

  // If close button has event
  if (digitalRead(closeButton) == LOW)
  {
    // Invoke startAcceleration
    startAcceleration(ccwPwmPin);
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

      // Invoke startAcceleration
      startAcceleration(cwPwmPin);

      break;

    // If button click 'ARROW DOWN' closes the sunschade
    case 0x52:

      // Invoke startAcceleration
      startAcceleration(ccwPwmPin);

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

  // Toggel Buzzer
  buzzer.turnOff();

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

  // Invoke stopSunshade
  sunshade.stopSunshade();

  // Write new value to output
  analogWrite(ccwPwmPin, 0);

  // Toggel Buzzer
  buzzer.turnOff();

  // delay(3000);
}

// Start Acceleration
void startAcceleration(int pwmPin)
{

  // Sunshade Condition
  if (pwmPin == cwPwmPin)
  {
    // Invoke openSunshde
    sunshade.openSunshade();
  }
  else
  {
    // Invoke closeSunshade
    sunshade.closeSunshade();
  }

  // Turn the motor clockwise (right)
  for (int i = ppwMin; i < ppwMax + 1; i++)
  {
    if (i > ppwMin)
    {
      // Write new value to output
      analogWrite(pwmPin, i);

      // Toggel Buzzer
      buzzer.toggle();
    }

    // Message
    messageln((String) "Accelerate Motor: Direction of Rotation 'clockwise' PWM value: " + i);

    // If button click 'ASTERIX' stops the motor
    if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x16 || digitalRead(stopButton) == LOW)
    {
      // Invoke Stop Acceleration
      stopAcceleration(pwmPin);

      // Exit the 'for' loop
      break;
    }
    IrReceiver.resume();

    // Message
    if (i == ppwMax)
    {
      messageln((String) "Motor reached the maximum speed.");
    }
  }
}