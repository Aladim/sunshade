// Include hardware
#include <Arduino.h>
#include <string.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DECODE_NEC
#include <IRremote.hpp>

// Include libraries
#include <Aladim-Sunshade.h>
#include <Aladim-BuzzerController.h>
#include <Aladim-LCDController.h>

/*
 * https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino
 * STOP using Serial.print in your Arduino code! THIS is better: https://www.youtube.com/watch?v=--KxxMaiwSE
 */

// IR reciver input pin 8 (S-to-8)
int IR_RECEIVE_PIN = 8;

// Create sunshade object
Aladim_Sunshade sunshade;

// Create buzzer object (S-to-12)
Aladim_BuzzerController buzzer(12);

// Create LCD object (SCL-to-SLC, SLA-to-SLA)
LiquidCrystal_I2C lcdDisplay = LiquidCrystal_I2C(0x27, 16, 2);

// Define operation mode
#define OperationMode 1

// Pin Number for the manual stop button
int stopButton = 7;

// Pin Number for the manual open sunshade
int openButton = 4;

// Pin Number for the manual close sunshade
int closeButton = 2;

// Pin for clockwise PWM signal (1-to-5)
int cwPwmPin = 5;

// Pin for counterclockwise PWM signal (2-to-6)
int ccwPwmPin = 6;

// Puls Power Modulation Minimum
int ppwMin = 100;

// Puls Power Modultion Maximum (Max: 255)
int ppwMax = 240;

// Stop Acceleration
void stopAcceleration(int pwmPin);

// Stop Acceleration
void startAcceleration(int pwmPin);

// Stop Motor
void stopMotor();

// Display Text
void displayMessage(String param_1, String param_2);

// Define a output methode for messages
#if OperationMode == 1
#define debug(param) Serial.print(param)
#define debugln(param) Serial.println(param)
#else
#define debug(param)
#define debugln(param)
#endif

// Message: Just to know which program is running on my Arduino
String strProgramStart_1 = "START 'SUNSHADE'";
String strProgramStart_2 = "WAIT FOR EVENT";

// String strProgramStart_1 = "HALLO 'LUTZ'";
// String strProgramStart_2 = "ALTES HAUS :-)";

// Message: STOP MOTOR
String strStopMotor_1 = "MOTOR: STOP";
String strStopMotor_2 = "WAIT FOR EVENT";

// Message: "Motor reached the maximum speed."
String strMotorMaxSpeed_1 = "MOTOR: MAX SPEED";
String strMotorMaxSpeed_2 = "PMW VALUE:";

//
// debugln((String) "Accelerate Motor: Direction of Rotation 'clockwise' PWM value: " + i);
String strAccelerateMotor_1 = "MOTOR: ROTATE:";
String strAccelerateMotor_2 = "PMW VALUE:";
String strCw = "CW";
String strCCw = "CCW";

// Message: Received noise or an unknown (or not yet enabled) protocol
String strUnknownProtocol_1 = "IRR: UNKNOWN";
String strUnknownProtocol_2 = "PROTOCOL RECIVED";

// setup
void setup()
{

  // Initialize the LC Display
  lcdDisplay.init();

  // Turn on the backlight
  lcdDisplay.backlight();

  // Start the serial monitor
  Serial.begin(9600);

  // Debug Message - Just to know which program is running on my Arduino
  debugln("START " __FILE__ " from " __DATE__ "Using library version " VERSION_IRREMOTE);

  // Message - Just to know which program is running on my Arduino
  displayMessage(strProgramStart_1, strProgramStart_2);

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
      // Display Messgae
      displayMessage(strUnknownProtocol_1, strUnknownProtocol_2);

      // Debug Message
      debugln("Received noise or an unknown (or not yet enabled) protocol");

      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }

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

/***********************************************************************************
 * Helper Methods ******************************************************************
 **********************************************************************************/

/*
 *Stop the motor
 */
void stopMotor()
{

  // Message
  debugln("Stop the Motor!");

  // LCD Message
  displayMessage(strStopMotor_1, strStopMotor_2);

  // Invoke stopMotor
  sunshade.stopSunshade();

  // Toggel Buzzer
  buzzer.turnOff();

  // Write new value to output
  analogWrite(cwPwmPin, 0);

  // Write new value to output
  analogWrite(ccwPwmPin, 0);
}

/*
 * Start Acceleration
 */
void startAcceleration(int pwmPin)
{

  // Temp Variable for rotation
  String strTempRotation;

  // Sunshade Condition
  if (pwmPin == cwPwmPin)
  {
    // Invoke openSunshde
    sunshade.openSunshade();

    // Set Rotation
    strTempRotation = strCw;
  }
  else
  {
    // Invoke closeSunshade
    sunshade.closeSunshade();

    // Set Rotation
    strTempRotation = strCCw;
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

    // Debug Message
    debugln((String) "Accelerate Motor: Direction of Rotation '" + strTempRotation + "' PWM value: " + i);

    // Display Message
    displayMessage(strAccelerateMotor_1, String(strAccelerateMotor_2 + i));

    // If button click 'ASTERIX' stops the motor
    if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x16 || digitalRead(stopButton) == LOW)
    {
      // Invoke Stop Motor
      stopMotor();

      // Exit the 'for' loop
      break;
    }
    IrReceiver.resume();

    // Message
    if (i == ppwMax)
    {
      // Debug Message
      debugln("Motor reached the maximum speed.");

      // Display Message
      displayMessage(strMotorMaxSpeed_1, String(strMotorMaxSpeed_2 + i));
    }
  }
}

/*
 *Display Text Message
 */
void displayMessage(String param_1, String param_2)
{

  lcdDisplay.clear();

  lcdDisplay.setCursor(0, 0);
  lcdDisplay.print(param_1);

  if (param_2 != "")
  {
    lcdDisplay.setCursor(0, 1);
    lcdDisplay.print(param_2);
  }
  else
  {
    lcdDisplay.setCursor(0, 1);
    lcdDisplay.print(millis() / 1000);
  }

  delay(100);
}