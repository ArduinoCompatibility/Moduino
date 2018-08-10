#include "Moduino.h"

Moduino::Moduino() {}
Moduino::~Moduino() {}

void Moduino::init()
{
	m_mcpCAN = &MCP_CAN(10);
	m_mcpCAN->begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
	m_mcpCAN->setMode(MCP_NORMAL);
	pinMode(2, INPUT);

	modules[0] = new LED(m_mcpCAN);//Temporary code. modules[0] LED fix.
}

char* Moduino::ReceiveMessage()
{
	INT32U rxId;
	unsigned char len = 0;
	unsigned char rxBuf[8];

	char msgString[128];
	char *pmsgString;
	m_mcpCAN->readMsgBuf(&rxId, &len, rxBuf);

	sprintf(msgString, "ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
	pmsgString = msgString + 29;

	for (int i = 0; i < len; i++)
	{
		sprintf(pmsgString, " 0x%.2X", rxBuf[i]);
		pmsgString += 5;
	}

	return msgString;
}

void LED::setRGB(INT8U red, INT8U green, INT8U blue)
{
	byte data[8] = { 0x00, red, 0x00, green, 0x00, blue, 0x00, 0x00 };

	INT32U txID = 0x04C10000;
	txID |= m_ID;

	p_mcpCAN->sendMsgBuf(txID, 1, 6, data);//(ID, extended flag, data length, data)
}