#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 10
#define CSN_PIN 9

const uint64_t pipe = 0xE8E8F0F0E1LL;
const int maxAxis = 660;
const int minAxis = 0;

bool receiverDebug = false;

RF24 radio(CE_PIN, CSN_PIN);
int joystick[9];

int xAxis, yAxis;
int BUTTON_A;
int BUTTON_B;
int BUTTON_C;
int BUTTON_D;
int BUTTON_E;
int BUTTON_F;
int BUTTON_G;

void setupReceiver()
{
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loopReceiver()
{
  if (radio.available())
  {
    radio.read(joystick, sizeof(joystick));
    xAxis = (joystick[0] > maxAxis) ? maxAxis : joystick[0];
    yAxis = (joystick[1] > maxAxis) ? maxAxis : joystick[1];

    BUTTON_A = joystick[2];
    BUTTON_B = joystick[3];
    BUTTON_C = joystick[4];
    BUTTON_D = joystick[5];
    BUTTON_E = joystick[6];
    BUTTON_F = joystick[7];
    BUTTON_G = joystick[8];

    if (receiverDebug)
    {
      Serial.print("X = ");
      Serial.print(xAxis);
      Serial.print(" Y = ");
      Serial.print(yAxis);
      Serial.print(" Up = ");
      Serial.print(BUTTON_A);
      Serial.print(" Right = ");
      Serial.print(BUTTON_B);
      Serial.print(" Down = ");
      Serial.print(BUTTON_C);
      Serial.print(" Left = ");
      Serial.print(BUTTON_D);
      Serial.print(" E = ");
      Serial.print(BUTTON_E);
      Serial.print(" F = ");
      Serial.print(BUTTON_F);
      Serial.print(" G = ");
      Serial.println(BUTTON_G);
    }
  }
}