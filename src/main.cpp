#include <Arduino.h>
#define led 13   // led on pin A13
#define button 8 // button on pin IN 8

void setup()
{
  // put your setup code here, to run once:

  // led
  pinMode(led, OUTPUT);

  // button
  pinMode(button, INPUT_PULLUP);

  // Start the serial monitor
  Serial.begin(9600);
}

void loop()
{

  // Test Loop
  // digitalWrite(led,HIGH);
  // delay(1000);

  // digitalWrite(led,LOW);
  // delay(1000);


  // put your main code here, to run repeatedly:
  if (digitalRead(button) == true)
  {

    // Print
    Serial.print("button true\n");

    // set led to high
    digitalWrite(led, HIGH);

    // set delay
    delay(6000);
  }
  else
  {

    // Print
    Serial.print("button false\n");

    // set led to low
    digitalWrite(led, LOW);

    // set delay
    delay(3000);
  }
  // Print
  // Serial.print("loop completed\n");
}