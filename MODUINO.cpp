#include "Moduino.h"

Moduino::Moduino() {}
Moduino::~Moduino() {}

void Moduino::init()
{
	modi_CAN.initMCP();
	modules[0] = new LED(&modi_CAN);//Temporary code. modules[0] LED fix.
}