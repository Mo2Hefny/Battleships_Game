#ifndef _WARSHIP_SHIP_
#define _WARSHIP_SHIP_

#include "Ship.h"

class Warship : public Ship
{
	Texture img;
	double width, height;

public:
	Warship(RenderWindow&);

	//setters

	//getters
};

#endif