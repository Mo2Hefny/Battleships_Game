#ifndef _COMPUTER_
#define _COMPUTER_

#include "Character.h"
#include <cstdlib>
#include <time.h>

class Computer : public Character
{
public:
	Computer(RenderWindow& window, Grid* grid);
	~Computer();
	void draw();

	//Preparation Phase
	void PrepPhase();
	void Randomizer();
	void PickRotation(Ship*);
	void PickPosition(Ship*);
	void PickMovement(Ship*);

	//getters
		
	//setters
};


#endif