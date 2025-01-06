#include <Arduino.h>
#include <Servo.h>
#include "CRSFforArduino.hpp"

#define LEDPIN PC13
#define SERVO1 PB13

CRSFforArduino crsf;
Servo servo1;

const int rcChannelCount = 12;

// Array of function pointers for handling channel-specific behavior
void (*channelHandlers[rcChannelCount])(int value);

// Function declarations
void handleChannel1(int value);
void handleChannel2(int value);
void handleChannel3(int value);
void handleChannel4(int value);
void handleChannel5(int value);
void handleChannel6(int value);
void handleChannel7(int value);
void handleChannel8(int value);
void handleChannel9(int value);
void handleChannel10(int value);
void handleChannel11(int value);
void handleChannel12(int value);

int mapToServo(int value);

// Default handler for unhandled channels
void defaultHandler(int value);

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels);

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);
  servo1.attach(SERVO1);

  // Initialise CRSF for Arduino
  if (!crsf.begin())
  {
    while (1)
    {
      delay(10); // Infinite loop if initialization fails
    }
  }

  crsf.setRcChannelsCallback(onReceiveRcChannels);

  // Initialize channel handlers
  for (int i = 0; i < rcChannelCount; i++)
  {
    channelHandlers[i] = defaultHandler; // Assign default handler
  }

  // Set specific handlers for certain channels
  channelHandlers[0] = handleChannel1; // C1x
  channelHandlers[1] = handleChannel2; // C1y
  channelHandlers[2] = handleChannel3; // C2x
  channelHandlers[3] = handleChannel4; // C2y
  channelHandlers[4] = handleChannel5; // Aux5
  channelHandlers[5] = handleChannel6; // Aux6
  channelHandlers[6] = handleChannel7; // Aux7
  channelHandlers[7] = handleChannel8; // Aux8
  channelHandlers[8] = handleChannel9; // Aux9
  channelHandlers[9] = handleChannel10; // Aux10
  channelHandlers[10] = handleChannel11; // Aux11
  channelHandlers[11] = handleChannel12; // Aux12
}

void loop()
{
  crsf.update();
}

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels)
{
  for (int i = 0; i < rcChannelCount; i++)
  {
    int channelValue = crsf.getChannel(i + 1); // CRSF channels are 1-based
    channelHandlers[i](channelValue);         // Call the appropriate handler
  }
}

int mapToServo(int value){
  int val = value;
  val = map(val, 0, 2000, 0, 180);
  return val;
}

// CHANNEL HANDLERS
void defaultHandler(int value)
{

}
void handleChannel1(int value)
{
  int val = mapToServo(value);
  servo1.write(val);
  delay(10);
}

void handleChannel2(int value)
{

}

void handleChannel3(int value)
{

}

void handleChannel4(int value)
{

}

void handleChannel5(int value)
{

}

void handleChannel6(int value)
{

  if (value > 1001)
  {
    digitalWrite(LEDPIN, LOW);
  }
  else
  {
    digitalWrite(LEDPIN, HIGH);
  }
}

void handleChannel7(int value)
{

}

void handleChannel8(int value)
{

}

void handleChannel9(int value)
{

}

void handleChannel10(int value)
{

}

void handleChannel11(int value)
{

}

void handleChannel12(int value)
{

}