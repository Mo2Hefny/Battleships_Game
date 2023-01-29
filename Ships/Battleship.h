#ifndef _BATTLESHIP_SHIP_
#define _BATTLESHIP_SHIP_

#include "Ship.h"

class Battleship : public Ship
{
	Texture img;
	double width, height;

public:
	Battleship(RenderWindow&);

	//setters

	//getters
};

#endif