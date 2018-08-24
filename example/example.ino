#include "Moduino.h"

Moduino modi;
LED *led0;
LED *led1;
Dial *dial0;
Button *button0;

void setup()
{
  //** Essential Code **
  modi.init();

  //** Your Code **
  led0=modi.addLED(0xA81);//Change to your module ID
  led1=modi.addLED(0xEEC);
  dial0=modi.addDial(0x27A);
  button0=modi.addButton(0xD1);

  modi.RequestProperty(button0);
  modi.RequestProperty(dial0);
  modi.FindID();//Get your module ID
}

void loop()
{
  //** Essential Code **
  modi.ReceiveProcess();

  //** Your Code **
  if(button0->getClick())
  {
    led0->setRGB(button0->getClick(),0,0);
    led1->setRGB(0,0,0);
  }
  else
  {
    led0->setRGB(0,dial0->getDegree(),0);
    led1->setRGB(0,0,dial0->getDegree());
  }
}

