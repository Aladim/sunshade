// Include hardware
#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>
#include <Aladim-Sunshade.h>

/*
 * https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino
 */

// IR reciver input pin  8
int IR_RECEIVE_PIN = 8;

// Create sunshade object
Aladim_Sunshade sunshade;

// Create motot object
// Aladim_MotorDriver motorDriver(5, 6);

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
 * The Main Loop
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
     * Switch for the revieved IrReceiver data
     */
    switch (IrReceiver.decodedIRData.command)
    {
    case 0x18:                      // If button click 'ARROW UP' opens the sunschade
      sunshade.openSunshade();      // invoke openSunshde
                                    // Turn the motor clockwise (right)
      for (int i = 0; i < 255; i++) // Increment current PWM value
      {
        analogWrite(5, i); // Write new value to output
        // Print
        Serial.println((String) "Accelerate Motor: Direction of Rotation 'clockwise' PWM value: " + i);

        // If button click 'ASTERIX' stops the motor
        if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x16)
        {
          Serial.println((String) "Accelerate Motor was stop!");
          analogWrite(5, 0); // Write new value to output
          IrReceiver.resume();
          break; // Exit the 'for' loop
        }
      }
      break;
    case 0x52:                      // If button click 'ARROW DOWN' closes the sunschade
      sunshade.closeSunshade();     // invoke closeSunshade
                                    // Turn the motor counterclockwise (left)
      for (int i = 0; i < 255; i++) // Increment current PWM value
      {
        analogWrite(6, i); // Write new value to output
        // Print
        Serial.println((String) "Accelerate Motor: Direction of Rotation 'counterclockwise' PWM value: " + i);

        // If button click 'ASTERIX' stops the motor
        if (IrReceiver.decode() && IrReceiver.decodedIRData.command == 0x16)
        {
          Serial.println((String) "Accelerate Motor was stop!");
          analogWrite(6, 0); // Write new value to output
          IrReceiver.resume();
          break; // Exit the 'for' loop
        }
      }
      break;
    case 0x16: // If button click 'ASTERIX' stops the motor
               // Print
      Serial.print("Stop the motor\n");
      sunshade.stopSunshade(); // invoke stopMotor
      analogWrite(5, 0);       // Write new value to output
      analogWrite(6, 0);       // Write new value to output
      break;
    case 0x5A:                   // If button click 'ASTERIX' turn on the warning light
      sunshade.warningLightOn(); // Invoke warningLightOn
      break;
    case 0xD:                     // If button click 'HASHTAG' turn off the warning light
      sunshade.warningLightOff(); // invoke warningLightOff
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