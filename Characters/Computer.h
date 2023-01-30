#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"
#include <cstdlib>
#include <time.h>

class Computer : public Character
{
	int enemy_placement[10][10];
	Ship* enemy_ships[5];
	Player* player;
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
	void PickTarget(Vector2i&);
	bool CheckShips(Vector2i&);
	bool CheckArea(Vector2i&, int, int);

	//getters
		
	//setters
	void setEnemyInfo(Player*);
};


#endif