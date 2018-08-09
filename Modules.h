#include "mcp_can.h"

class ModiCAN
{
public:
	MCP_CAN *mcp_CAN;

	ModiCAN() {}
	~ModiCAN() {}

	void initMCP()
	{
		mcp_CAN = &MCP_CAN(10);
		mcp_CAN->begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ);
		mcp_CAN->setMode(MCP_NORMAL);
		pinMode(2, INPUT);
	}

	void SendMessage(INT32U ins, INT32U sid, INT32U did, INT8U data[], int len)
	{
		INT32U txID = 0;
		txID |= (ins << 24);
		txID |= (sid << 12);
		txID |= did;

		mcp_CAN->sendMsgBuf(txID, 1, len, data);//(ID, extended flag, data length, data)
	}

	char* ReceiveMessage()
	{
		INT32U rxId;
		unsigned char len = 0;
		unsigned char rxBuf[8];

		char msgString[128];
		mcp_CAN->readMsgBuf(&rxId, &len, rxBuf);

		sprintf(msgString, "ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
		for (int i = 0; i < len; i++) sprintf(msgString, " 0x%.2X", rxBuf[i]);

		return msgString;
	}
};

class Module
{
public:
	ModiCAN *p_modiCAN;

	Module(ModiCAN *modiCAN) { p_modiCAN = modiCAN; }
	~Module() {}
};

class LED : public Module
{
private:
	INT32U m_ID;
public:
	LED(ModiCAN *modiCAN) : Module(modiCAN) { m_ID = 0xFFF; }//Temporary code. m_ID fixed(0xFFF).
	~LED() {}

	void setRGB(INT8U, INT8U, INT8U);
};