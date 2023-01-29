#ifndef _SUBMARINE_SHIP_
#define _SUBMARINE_SHIP_

#include "Ship.h"

class Submarine : public Ship
{
	Texture img;
	double width, height;

public:
	Submarine(RenderWindow&);

	//setters

	//getters
};

#endif