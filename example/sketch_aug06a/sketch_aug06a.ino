#include "Moduino.h"

Moduino modi;
LED *led;

void setup()
{
  modi.init();
  led=modi.modules[0];//modules[0] LED fixed(temporarily).
}

void loop()
{
  //simple led blink
  led->setRGB(100,0,0);
  delay(500);
  led->setRGB(0,0,0);
  delay(500);
}
