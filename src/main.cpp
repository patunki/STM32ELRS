
#include <Arduino.h>
#include "CRSFforArduino.hpp"
#define USE_SERIAL_PLOTTER 0

#define LEDPIN PC13

CRSFforArduino *crsf = nullptr;

int rcChannelCount = 12;
const char *rcChannelNames[] = {
    "C1x",
    "C1y",
    "C2y",
    "C2x",
    "Aux1",
    "Aux2",
    "Aux3",
    "Aux4",
    "Aux5",
    "Aux6",
    "Aux7",
    "Aux8",
    "Aux9"
    };

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels);

void setup()
{
  pinMode(LEDPIN, OUTPUT);
  // Initialise the serial port & wait for the port to open.
  Serial.begin(115200);
  while (!Serial)
  {
      ;
  }

  // Initialise CRSF for Arduino.
  crsf = new CRSFforArduino();
  if (!crsf->begin())
  {
      crsf->end();

      delete crsf;
      crsf = nullptr;

      Serial.println("CRSF for Arduino initialisation failed!");
      while (1)
      {
          delay(10);
      }
  }


  crsf->setRcChannelsCallback(onReceiveRcChannels);

  // Show the user that the sketch is ready.
  Serial.println("RC Channels Example");
  delay(1000);
  Serial.println("Ready");
  delay(1000);
}

void loop()
{
    crsf->update();
    if (crsf->getChannel(6) > 1001){
      digitalWrite(LEDPIN, LOW);
    } else {
      digitalWrite(LEDPIN, HIGH);
    }
}

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels)
{
    if (rcChannels->failsafe == false)
    {
        /* Print RC channels every 100 ms. */
        unsigned long thisTime = millis();
        static unsigned long lastTime = millis();

        /* Compensate for millis() overflow. */
        if (thisTime < lastTime)
        {
            lastTime = thisTime;
        }

        if (thisTime - lastTime >= 100)
        {
            lastTime = thisTime;

            Serial.print("RC Channels <");
            for (int i = 1; i <= rcChannelCount; i++)
            {
                Serial.print(rcChannelNames[i - 1]);
                Serial.print(": ");
                Serial.print(crsf->rcToUs(crsf->getChannel(i)));

                if (i < rcChannelCount)
                {
                    Serial.print(", ");
                }
            }
            Serial.println(">");
        }
    }
}