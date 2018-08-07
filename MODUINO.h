#include "mcp_can.h"

class Moduino
{
private:
	MCP_CAN *m_CAN;
public:
	Moduino();
	~Moduino();
	void setRGB(byte, byte, byte);
};