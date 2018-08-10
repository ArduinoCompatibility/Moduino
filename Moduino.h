#include "mcp_can.h"

class Module
{
public:
	MCP_CAN *p_mcpCAN;

	Module(MCP_CAN *mcpCAN) { p_mcpCAN = mcpCAN; }
	~Module() {}
};

class LED : public Module
{
private:
	INT32U m_ID;
public:
	LED(MCP_CAN *mcpCAN) : Module(mcpCAN) { m_ID = 0xFFF; }//Temporary code. m_ID fixed(0xFFF).
	~LED() {}

	void setRGB(INT8U, INT8U, INT8U);
};

class Moduino
{
public:
	MCP_CAN *m_mcpCAN;
	Module *modules[8];
	Moduino();
	~Moduino();
	void init();
	char* ReceiveMessage();
};