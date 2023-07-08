// Include hardware
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
// #include <Aladim_LedController.h>
#include <Aladim-Sunshade.h>

/*
 * https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino
 */
int IR_RECEIVE_PIN = 8; // IR reciver input pin  8

// Create sunshade object
Aladim_Sunshade sunshade;

// setup
void setup()
{
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the serial monitor
  Serial.begin(9600);

  // Create IR receiver object
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

/*
 * Main Loop
 */
void loop()
{

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
      sunshade.openSunshade();
    }
    // If button click 'ARROW DOWN' closes the sunschade
    else if (IrReceiver.decodedIRData.command == 0x52)
    {
      // invoke closeSunshade
      sunshade.closeSunshade();
    }
    // If button click 'OK' stop the motor
    else if (IrReceiver.decodedIRData.command == 0x1C)
    {
      // invoke stopMotor
      sunshade.stopSunshade();
    }
    // If button click 'ASTERIX' turn on the warning light
    else if (IrReceiver.decodedIRData.command == 0x16)
    {
      // invoke warningLightOn
      sunshade.warningLightOn();
    }
    // If button click 'HASHTAG' turn off the warning light
    else if (IrReceiver.decodedIRData.command == 0xD)
    {
      // invoke warningLightOff
      sunshade.warningLightOff();
    }
  }
}