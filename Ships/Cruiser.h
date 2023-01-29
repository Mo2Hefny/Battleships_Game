#ifndef _CRUISER_SHIP_
#define _CRUISER_SHIP_

#include "Ship.h"

class Cruiser : public Ship
{
	Texture img;
	double width, height;

public:
	Cruiser(RenderWindow&);

	//setters

	//getters
};

#endif