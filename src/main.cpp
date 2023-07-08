// Include hardware
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
#include <Aladim_LedController.h>

/*
 * https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino
 */
int IR_RECEIVE_PIN = 8; // IR reciver input pin  8

// Create LED object for open sunshade operation
Aladim_LedController ledOpenSunshade(9);

// Create LED object for the close sunshade operation
Aladim_LedController ledCloseSunshade(10);

// Create LED object for the stop motor operation
Aladim_LedController ledStopMotor(11);

// setup
void setup()
{
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the serial monitor
  Serial.begin(9600);

  // Start the receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

// open sunshade
void openSunshade()
{

  // Print
  Serial.print("open sunshade\n");

  // Turn on ledOpenSunshade
  ledOpenSunshade.turnOn();

  // set delay
  delay(3000);

  // Trun off ledOpenSunshade
  ledOpenSunshade.turnOff();
}

// open sunshade
void closeSunshade()
{

  // Print
  Serial.print("closing sunshade\n");

  // Turn on ledCloseSunshade
  ledCloseSunshade.turnOn();

  // set delay
  delay(3000);

  // Trun off ledCloseSunshade
  ledCloseSunshade.turnOff();
}

// stop motor
void stopMotor()
{
  // Print
  Serial.print("stop motor\n");

  // Turn on ledStopMotor
  ledStopMotor.turnOn();

  // set delay
  delay(3000);

  // Trun off ledStopMotor
  ledStopMotor.turnOff();
}

// turn warning light on
void warningLightOn()
{
  // Print
  Serial.print("turn on the warning light\n");
}

// turn warning light off
void warningLightOff()
{
  // Print
  Serial.print("turn off the warning light\n");
}

void loop()
{
  // put your main code here, to run repeatedly:

  // If IR reciver
  if (IrReceiver.decode())
  {
    // Print complete received data in one line
    IrReceiver.printIRResultShort(&Serial);

    // Print the statement required to send this data
    IrReceiver.printIRSendUsage(&Serial);

    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    /*
     * !!!Important!!! Enable receiving of the next value,
     * since receiving has stopped after the end of the current received data packet.
     */
    IrReceiver.resume();

    /*
     * Finally, check the received data and perform actions according to the received command
     */

    // If button click 'ARROW UP' opens the sunschade
    if (IrReceiver.decodedIRData.command == 0x18)
    {
      // invoke openSunshde
      openSunshade();
    }
    // If button click 'ARROW DOWN' closes the sunschade
    else if (IrReceiver.decodedIRData.command == 0x52)
    {
      // invoke closeSunshade
      closeSunshade();
    }
    // If button click 'OK' stop the motor
    else if (IrReceiver.decodedIRData.command == 0x1C)
    {
      // invoke stopMotor
      stopMotor();
    }
    // If button click 'ASTERIX' turn on the warning light
    else if (IrReceiver.decodedIRData.command == 0x16)
    {
      // invoke warningLightOn
      warningLightOn();
    }
    // If button click 'HASHTAG' turn off the warning light
    else if (IrReceiver.decodedIRData.command == 0xD)
    {
      // invoke warningLightOff
      warningLightOff();
    }
  }
}