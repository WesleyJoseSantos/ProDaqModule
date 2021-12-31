#include "ProDaqModule.h"

#define PRODAQ_TIMER 500 // Time between data exchange in ms
#define ITEMS_COUNT 6    // Items count attached to proDaq
#define BUF_SIZE 256     // Extimated buffer size to store json string

ProDaqSerial proDaq(PRODAQ_TIMER, ITEMS_COUNT, BUF_SIZE);

int count = 0;
long sLong = 0;
float sFloat = 0.0;
double sDouble = 0.0;
String sString = "Hello World!";
unsigned long timer = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(74400);
  proDaq.setPort(Serial);

  proDaq.attachObject(count);         // Attach object directly to proDaq using variable name.
  proDaq.attachObject(sLong);         // Attach object directly to proDaq using variable name.
  proDaq.attachObject(sFloat);        // Attach object directly to proDaq using variable name.
  proDaq.attachObject(sDouble);       // Attach object directly to proDaq using variable name.
  proDaq.attachObject(sString);       // Attach object directly to proDaq using variable name.
  proDaq.attachItem("millis", timer); // Give optional name to attached object.
}

void loop()
{
  // put your main code here, to run repeatedly:
  proDaq.task();

  count++;
  sLong += 10;
  sFloat += 0.25;
  sDouble += 0.5;
  timer = millis();
}