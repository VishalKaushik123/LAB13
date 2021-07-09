/*
 * Project LAB13
 * Description:
 * Author:
 * Date:
 */
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#include "oled-wing-adafruit.h"

OledWingAdafruit display;

int count = 0;
int interuptCount = 0;
volatile bool interruptOccured = false;

void isr()
{
  interruptOccured = false;
  if (interuptCount % 2 != 0)
  {
    interruptOccured = true;
  }
}

void setup()
{
  pinMode(D5, INPUT);                // Counter button
  pinMode(D6, INPUT_PULLUP);         // defaults to HIGH
  attachInterrupt(D6, isr, FALLING); // D6 will now generate an interrupt on the falling edge and will run the code in the isr

  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  display.loop();
  if (!interruptOccured)
  {
    // if counter button is pressed
    if (digitalRead(D5))
    {
      count++;
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print(count);
      display.display();
    }
  }
  
  // if interupt button is pressed
  if(digitalRead(D6)){
    interuptCount++;
  }
  delay(200);
}