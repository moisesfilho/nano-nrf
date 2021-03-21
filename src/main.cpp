#include <Arduino.h>
#include <CarControl.h>
#include <Braco.h>

int debug = false;

void setup()
{
  if (debug)
  {
    Serial.begin(9600);
    Serial.println("Tank Starting");
  }

  setupCarControl();
  setupBraco();
}

void loop()
{
  carControlDebug = debug;
  loopCarControl();
  loopBraco();
}
