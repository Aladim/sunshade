// Include hardware
#include <Arduino.h>
#include <string.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// IR Sensor
#define DECODE_NEC
#include <IRremote.h>

// Include libraries
#include <Aladim-Sunshade.h>
#include <Aladim-BuzzerController.h>
#include <Aladim-LCDController.h>

// WiFi
#include <WiFiNINA.h>
#include <ArduinoOTA.h>
#include "arduino_secrets.h" 
// WiFi credentials
// const char *ssid = "MsWlanBoxSunshade"; // your network SSID (name)
// const char *password = "023145390925031973"; // your network password

char ssid[] = SECRET_SSID;        // your network SSID (name)
char password[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS; // the Wifi radio's status

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

// Define Debug Mode
#define DebugMode 1

// Pin Number for the manual stop button
int stopButton = 7;

// Pin Number for the manual open sunshade
int openButton = 4;

// Pin Number for the manual close sunshade
int closeButton = 13;

// Pin for clockwise PWM signal (1-to-5)
int cwPwmPin = 5;

// Pin for counterclockwise PWM signal (2-to-6)
// int ccwPwmPin = 6;
int ccwPwmPin = 9;

// Puls Power Modulation Minimum (100)
int ppwMin = 200;

// Puls Power Modultion Maximum (Max: 255)
int ppwMax = 240;

// Measuring current using ACS712 - 5A, 20A and 30A modules

// analog data read from sensor
int rawValue;

// Value for analogRead(A0) should be 1024/2 = 512 if no current is floating
// const int motorZeroCurrentValue = 510;
int motorZeroCurrentValue;

// Value for analogRead(A0) should be 1024/2 = 512 if no current is floating
// const int motorZeroCurrentValue = 510;
int ledStripZeroCurrentValue;

// Sensitivity ratior of the current senns module
float scaleFactor = 0.100; // for 5A module = 185.0 // for 20A module = 100.0 // for 30A module = 66.0

// Variable for curent
float current = 0.0;

// Default set to 500mA
float maxCurrentLedStrip = 800.0;

// Default set to 2500mA
// float maxCurrent = 2500.0;
float maxCurrent = 2100.0;

// Pin Number for the Current Sensor
int currentSensorPin = 0;

// Variable for feedback
int motorCurrentMonitorFeedback = 0;

// Motor has stoped
int motorIsRunning = 0;

// Variable for feedback
int ledStripeCurrentMonitorFeedback = 0;

// Stop Acceleration
void stopAcceleration(int pwmPin);

// Stop Acceleration
void startAcceleration(int pwmPin);

// Stop Motor
void stopMotor();

// LED is still on, Stop Motor
void stopMotorLED();

// Display Text
void displayMessage(String param_1, String param_2);

// LED Stripes Current Sensor Monitoring
int ledStripCurrentSensorMonitoring();

// Current Sensor Monitoring
int motorCurrentSensorMonitoring();

// Define a output methode for messages
#if DebugMode == 1
#define debug(param) Serial.print(param)
#define debugln(param) Serial.println(param)
#else
#define debug(param)
#define debugln(param)
#endif

// Message: Just to know which program is running on my Arduino
String strProgramStart_1 = "START 'SUNSHADE'";
String strProgramStart_2 = "PRESS A BUTTON";

// Message: STOP MOTOR
String strStopMotor_1 = "MOTOR: STOP";
String strStopMotor_2 = "PRESS A BUTTON";
String strStopMotor_3 = "MOTOR BLOCKED";

// Message: "Motor reached the maximum speed." (Pulse-width modulation)
String strMotorMaxSpeed_1 = "MOTOR: MAX SPEED";
String strMotorMaxSpeed_2 = "PWM VALUE:";

// Message: Motor starts up (Pulse-width modulation)
String strAccelerateMotor_1 = "MOTOR: STARTS UP";
String strAccelerateMotor_2 = "PWM VALUE:";
String strCw = "CW";
String strCCw = "CCW";

// Message: Received noise or an unknown (or not yet enabled) protocol
String strUnknownProtocol_1 = "IRR: ERROR";
String strUnknownProtocol_2 = "UNKNOWN PROTOCOL";

// Message: Button Tool Tip
String strButtonToolTip_1 = "PRESS ARROW UP,";
String strButtonToolTip_2 = "ARROW DOWN OR OK";

// ***************************************************************
// ************* Setup *******************************************  
// ***************************************************************
void setup()
{
  // Initialize the LC Display
  lcdDisplay.init();

  // Turn on the backlight
  lcdDisplay.backlight();

  // Start the serial monitor
  Serial.begin(9600);

  // Debug Message - Just to know which program is running on my Arduino
  debugln("START " __FILE__ " from " __DATE__ " Using library version " VERSION_IRREMOTE);

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

  // Initialize LED Stripes Current Value
  ledStripZeroCurrentValue = analogRead(1);

  // Initialize Motor Current Value
  motorZeroCurrentValue = analogRead(0);

  // ***************************************************************
  // ************* Create WiFi Connection **************************
  // ***************************************************************
  // https://github.com/arduino-libraries/WiFiNINA/tree/master
  // Ensure WiFi is connected
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {

    Serial.println("Communication with WiFi module failed!");

    displayMessage("WIFI: ERROR", "NO MODULE");

    // don't continue
    while (true);
  }

  // Check the firmware version
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");

    displayMessage("WIFI: ERROR", "UPGRADE FIRMWARE");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED)
  {

    Serial.print("Attempting to connect to open SSID: ");

    displayMessage("WIFI: CONNECTING", ssid);

    Serial.println(ssid);

    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");

  displayMessage("WIFI: CONNECTED", ssid);
}

// *************************************************
// OTA - Over The Air Updates
// *************************************************

// start the WiFi OTA library with internal (flash) based storage
// ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);


// ***************************************************************
// ************* Loop ********************************************
// ***************************************************************
void loop()
{

  // Conditional invoke of the method Current Sensor Monitoring of the LED Stripes.
  if (ledStripCurrentSensorMonitoring() == 1 && motorIsRunning == 1)
  {
    // Invoke stopMotorLED
    stopMotorLED();
  }

  // Conditional invoke of the method Current Sensor Monitoring of the Motor.
  if (motorCurrentSensorMonitoring() == 1)
  {
    // Invoke stopMotor
    stopMotor();
  }

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

    // If button click 'OK' stops the motor
    case 0x1C:

      // Invoke stopMotor
      stopMotor();

      break;

    default:

      // Message
      debugln("Stop the Motor!");

      // LCD Message
      displayMessage(strButtonToolTip_1, strButtonToolTip_2);

      break;
    }

    /*
     * !!!Important!!! Enable receiving of the next value,
     * since receiving has stopped after the end of the current received data packet.
     */
    IrReceiver.resume();
  }

    // check for WiFi OTA updates
    ArduinoOTA.poll();
}

// **********************************************************************************
// ************* ### Helper Methods ### *********************************************
// **********************************************************************************

// ** Stop Motor Led **
void stopMotorLED()
{
  // Buzzer Beep
  buzzer.beep();

  // Message
  debugln("LED is still on, stop the Motor!");

  displayMessage(strStopMotor_1, "TURN OF LEDS");

  // Invoke stopMotor
  sunshade.stopSunshade();

  // Write new value to output
  analogWrite(cwPwmPin, 0);

  // Write new value to output
  analogWrite(ccwPwmPin, 0);

  // Write new vlaue
  motorIsRunning = 0;
}

 // ** Stop the motor **
void stopMotor()
{
  // Buzzer Beep
  buzzer.beep();

  // Message
  debugln("Stop the Motor!");

  // If condition for Current Monitor Feedback
  if (motorCurrentMonitorFeedback == 1)
  {
    // LCD Message
    displayMessage(strStopMotor_1, strStopMotor_3);
  }
  else
  {
    // LCD Message
    displayMessage(strStopMotor_1, strStopMotor_2);
  }

  // Invoke stopMotor
  sunshade.stopSunshade();

  // Write new value to output
  analogWrite(cwPwmPin, 0);

  // Write new value to output
  analogWrite(ccwPwmPin, 0);

  // Write new value
  motorIsRunning = 0;
}

// ** Start Acceleration **
void startAcceleration(int pwmPin)
{

  // Buzzer Beep
  buzzer.beep();

  // Conditional invoke of the method Current Sensor Monitoring of the LED Stripes.
  if (ledStripCurrentSensorMonitoring() == 1)
  {
    // Invoke stopMotorLED
    stopMotorLED();

    return;
  }

  // Write new value
  motorIsRunning = 1;

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

      // buzzer.toggle();
    }

    // Debug Message
    debugln((String) "Accelerate Motor: Direction of Rotation '" + strTempRotation + "' PWM value: " + i);

    // Display Message
    displayMessage(strAccelerateMotor_1, String(strAccelerateMotor_2 + i));

    // Motor Current Sensor Monitoring
    motorCurrentMonitorFeedback = motorCurrentSensorMonitoring();

    // Debugging Message
    debugln((String) "Motor Current Monitor Feedback: " + motorCurrentMonitorFeedback);

    /*
     * If button click 'OK' OR  stopButton == LOW OR motorCurrentMonitorFeedback == 1 then stops the motor
     */
    if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x1C || digitalRead(stopButton) == LOW || motorCurrentMonitorFeedback == 1)
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
 * LED Stripes Current Sensor Monitoring
 * https://wolles-elektronikkiste.de/acs712-stromsensor
 */

int ledStripCurrentSensorMonitoring()
{

  // Debugging Message
  debugln((String) "LED Zero Current Value: " + ledStripZeroCurrentValue);

  // Read raw data from ADC
  rawValue = analogRead(1);

  // Debugging Message
  debugln((String) "LED Analog Read Value: " + rawValue);

  // Calculate the actual current value
  // current = (rawValue - ledStripZeroCurrentValue) * 5.0 / 1.024 / 0.100;
  current = (rawValue - ledStripZeroCurrentValue) * 5.0 / 1.024 / scaleFactor;

  // Convert current if value has negative sign
  if (current < 0)
  {
    current *= -1.0;
  }

  // Stop the Motor if the LED Stripes current is higher then maxCurrentLedStrip
  if (current >= maxCurrentLedStrip)
  {
    // Debugg Message
    debugln((String) "LED Current Value is floating: " + current + " mA");

    return 1;
  }
  else
  {
    // Debugg Message
    debugln((String) "LED Current Value: " + current + "mA");

    return 0;
  }
}

/*
 * Motor Current Sensor Monitoring
 * https://wolles-elektronikkiste.de/acs712-stromsensor
 */

int motorCurrentSensorMonitoring()
{

  // Debugging Message
  debugln((String) "Motor Zero Current Value: " + motorZeroCurrentValue);

  // Read raw data from ADC
  rawValue = analogRead(0);

  // Debugging Message
  debugln((String) "Motor Analog Read Value: " + rawValue);

  // Calculate the actual current value
  // current = (rawValue - motorZeroCurrentValue) * 5.0 / 1.024 / 0.100;
  current = (rawValue - motorZeroCurrentValue) * 5.0 / 1.024 / scaleFactor;

  // Convert current if value has negative sign
  if (current < 0)
  {
    current *= -1.0;
  }

  // Stop the Motor if current is to high
  if (current >= maxCurrent)
  {
    // Debugg Message
    debugln((String) "Motor Current Value to hight: " + current + " mA");

    return 1;
  }
  else
  {
    // Debugg Message
    debugln((String) "Motor Current Value: " + current + "mA");

    return 0;
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

  delay(50);
}



// Format Selection (Ctrl+K Ctrl+F) - Format the selected text.