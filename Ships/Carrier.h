#ifndef _CARRIER_SHIP_
#define _CARRIER_SHIP_

#include "Ship.h"

class Carrier : public Ship
{
	Texture img;
	double width, height;
	
public:
	Carrier(RenderWindow&);

	//setters

	//getters
};

#endif