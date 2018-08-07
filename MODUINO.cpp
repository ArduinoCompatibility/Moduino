#include "MODUINO.h"

Moduino::Moduino()
{
	m_CAN = new MCP_CAN(10);
	m_CAN->begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
	m_CAN->setMode(MCP_NORMAL);
}

Moduino::~Moduino()
{
	delete m_CAN;
}

void Moduino::setRGB(byte red, byte green, byte blue)
{
	byte data[8] = { 0x00, red, 0x00, green, 0x00, blue, 0x00, 0x00 };
	m_CAN->sendMsgBuf(0x04C10FFF, 1, 6, data);
}