#include "Modules.h"

class Moduino
{
private:
	ModiCAN modi_CAN;
public:
	Module *modules[8];
	Moduino();
	~Moduino();
	void init();
};