#include "Moduino.h"

Moduino modi;
LED *led;

char *msgString;                        // Array to store serial string

void setup()
{
  Serial.begin(115200);
  modi.init();
  led=modi.modules[0];//modules[0] LED fixed(temporarily).
}

void loop()
{
  if(!digitalRead(2))                         // If CAN0_INT pin is low, read receive buffer
  {
    msgString=led->p_modiCAN->ReceiveMessage();
    Serial.println(msgString);
  }
}
