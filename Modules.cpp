#include "Modules.h"

void LED::setRGB(INT8U red, INT8U green, INT8U blue)
{
	byte data[8] = { 0x00, red, 0x00, green, 0x00, blue, 0x00, 0x00 };
	p_modiCAN->SendMessage(0x04, 0xC10, m_ID, data, 6);
}