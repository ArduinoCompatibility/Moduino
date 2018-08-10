#include "Moduino.h"

Moduino modi;
LED *led;
char *rxmsg;

void setup()
{
  Serial.begin(115200);
  attachInterrupt(digitalRead(2),getMessage,LOW);
  modi.init();
  led=modi.modules[0];//modules[0] LED fixed(temporarily).
}

void loop()
{
  led->setRGB(100,100,0);
  delay(500);
  led->setRGB(0,0,0);
  delay(500);
}

void getMessage()
{
  rxmsg=modi.ReceiveMessage();
  Serial.println(rxmsg);
}


