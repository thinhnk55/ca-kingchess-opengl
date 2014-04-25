#include "Graphic.h"


Graphic::Graphic(void)
{
	near_height = 0.5;
	zNear = 1;
	zFar = 1000;
    screenWidth = 600;
    screenHeight = 600;
}

Graphic& Graphic::inst()
{
	static Graphic Instance;
	return Instance;
}

Graphic::~Graphic(void)
{
}
