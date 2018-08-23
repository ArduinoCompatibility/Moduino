#include "Moduino.h"

//////// Moduino Functions ////////


void Moduino::init()
{
	m_mcpCAN = &MCP_CAN(10);
	m_mcpCAN->begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
	m_mcpCAN->setMode(MCP_NORMAL);
	pinMode(2, INPUT);
	for (int i = 0; i < 8; i++) modules[i] = NULL;

	Serial.begin(1000000);
	Serial.println("Moduino - Init Complete.");
}

void Moduino::FindID()
{
	INT8U findID[8] = { 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	m_mcpCAN->sendMsgBuf(0x08000FFF, 1, 8, findID);
}

void Moduino::RequestProperty(Module* module)
{
	INT32U txID = 0x03000000;
	txID |= module->getID();
	INT8U findID[4] = { 0x00, 0x00, 0x61, 0x00 };
	m_mcpCAN->sendMsgBuf(txID, 1, 8, findID);
}

bool Moduino::ReceiveProcess()
{
	if (digitalRead(2)) return false;

	INT32U rxId = 0;
	INT32U INS = 0;
	INT32U SID = 0;
	INT32U DID = 0;
	unsigned char len = 0;
	unsigned char rxBuf[8] = {};

	m_mcpCAN->readMsgBuf(&rxId, &len, rxBuf);

	rxId = rxId & 0x1FFFFFFF;
	INS = rxId >> 24;
	SID = (rxId & 0x00FFF000) >> 12;
	DID = rxId & 0x00000FFF;

	if (INS == 0)//case Health
	{
		//Serial.print(SID, HEX);
		//Serial.println(" Health received.");
		return true;
	}
	else if (INS == 0x05)//case AssignID
	{
		INT32U ModuleID = rxBuf[5];
		ModuleID = ModuleID << 8;
		ModuleID = ModuleID | rxBuf[4];

		if (ModuleID == 0x0000) Serial.print("AssignID received. Module Network - ID: 0x");//case Network
		else if (ModuleID == 0x2000) Serial.print("AssignID received. Module Environment - ID: 0x");//case Environment
		else if (ModuleID == 0x2010) Serial.print("AssignID received. Module Gyroscope - ID: 0x");//case Gyroscope
		else if (ModuleID == 0x2020) Serial.print("AssignID received. Module Mic - ID: 0x");//case Mic
		else if (ModuleID == 0x2030) Serial.print("AssignID received. Module Button - ID: 0x");//case Button
		else if (ModuleID == 0x2040) Serial.print("AssignID received. Module Dial - ID: 0x");//case Dial
		else if (ModuleID == 0x2050) Serial.print("AssignID received. Module Ultrasonic - ID: 0x");//case Ultrasonic
		else if (ModuleID == 0x2060) Serial.print("AssignID received. Module IR - ID: 0x");//case IR
		else if (ModuleID == 0x4000) Serial.print("AssignID received. Module Display - ID: 0x");//case Display
		else if (ModuleID == 0x4010) Serial.print("AssignID received. Module Motor - ID: 0x");//case Motor
		else if (ModuleID == 0x4020) Serial.print("AssignID received. Module LED - ID: 0x");//case LED
		else if (ModuleID == 0x4030) Serial.print("AssignID received. Module Speaker - ID: 0x");//case Speaker

		Serial.println(SID, HEX);
		return true;
	}
	else if (INS == 0x10)//case Warning
	{
		Serial.print(SID, HEX);
		Serial.println(" Warning received.");
		return true;
	}
	else if (INS == 0x1F)//case ChannelProperty
	{
		//Serial.print(SID, HEX);
		//Serial.println(" ChannelProperty received.");
		for (int i = 0; i < 8; i++)
		{
			if (modules[i]->getID() == SID)
			{
				if (modules[i]->getUUID() == 0x2030)//case Button
				{
					Button* temp = (Button*)modules[i];
					temp->setClick(rxBuf[0]);
					return true;
				}
				else if (modules[i]->getUUID() == 0x2040)//case Dial
				{
					Dial* temp = (Dial*)modules[i];
					temp->setDegree(rxBuf[0]);
					return true;
				}
			}
		}
		return false;
	}
	return false;
}

//////// Add Module Functions ////////


LED* Moduino::addLED(INT32U ID)
{
	if (modules[7]) return NULL;//Modulelist is Full

	int listseq = 0;
	while (modules[listseq]) listseq++;
	modules[listseq] = new LED(m_mcpCAN, ID, 0x4020);
	return modules[listseq];
}

Button* Moduino::addButton(INT32U ID)
{
	if (modules[7]) return NULL;//Modulelist is Full

	int listseq = 0;
	while (modules[listseq]) listseq++;
	modules[listseq] = new Button(m_mcpCAN, ID, 0x2030);
	return modules[listseq];
}

Dial* Moduino::addDial(INT32U ID)
{
	if (modules[7]) return NULL;//Modulelist is Full

	int listseq = 0;
	while (modules[listseq]) listseq++;
	modules[listseq] = new Dial(m_mcpCAN, ID, 0x2040);
	return modules[listseq];
}

//////// Module Functions ////////


void LED::setRGB(INT8U red, INT8U green, INT8U blue)
{
	INT8U data[8] = { red, 0x00, green, 0x00, blue, 0x00, 0x00, 0x00 };

	INT32U txID = 0x04C10000;
	txID |= getID();

	getMCP()->sendMsgBuf(txID, 1, 8, data);//(ID, extended flag, data length, data)
}
