#include "mcp_can.h"

class Module
{
private:
	INT32U m_ID;
	INT32U m_UUID;
	MCP_CAN *p_mcpCAN;
public:
	Module(MCP_CAN *mcpCAN, INT32U ID, INT32U UUID) { m_ID = ID; m_UUID = UUID; p_mcpCAN = mcpCAN; }
	~Module() {}

	void setID(INT32U ID) { m_ID = ID; }
	INT32U getID() { return m_ID; }
	INT32U getUUID() { return m_UUID; }
	MCP_CAN* getMCP() { return p_mcpCAN; }
};

class LED : public Module
{
public:
	LED(MCP_CAN *mcpCAN, INT32U ID, INT32U UUID) : Module(mcpCAN, ID, UUID) {}
	~LED() {}

	void setRGB(INT8U, INT8U, INT8U);
};

class Button : public Module
{
private:
	INT8U click;
public:
	Button(MCP_CAN *mcpCAN, INT32U ID, INT32U UUID) : Module(mcpCAN, ID, UUID) { click = 0; }
	~Button() {}

	void setClick(INT8U cl) { click = cl; }
	INT8U getClick() { return click; }
};

class Dial : public Module
{
private:
	INT8U degree;
public:
	Dial(MCP_CAN *mcpCAN, INT32U ID, INT32U UUID) : Module(mcpCAN, ID, UUID) { degree = 0; }
	~Dial() {}

	void setDegree(INT8U deg) { degree = deg; }
	INT8U getDegree() { return degree; }
};

class Moduino
{
private:
	MCP_CAN *m_mcpCAN;
	Module *modules[8];
public:
	Moduino() {}
	~Moduino() {}
	void init();
	void FindID();
	void RequestProperty(Module*);
	bool ReceiveProcess();

	LED* addLED(INT32U);
	Button* addButton(INT32U);
	Dial* addDial(INT32U);
};