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
	}

	void SendMessage(INT32U ins, INT32U sid, INT32U did, INT8U data[], int len)
	{
		INT32U extID;
		extID |= (ins << 24);
		extID |= (sid << 12);
		extID |= did;

		mcp_CAN->sendMsgBuf(extID, 1, len, data);//(ID, extended flag, data length, data)
	}

	void ReceiveMessage()
	{

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