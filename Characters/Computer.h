#ifndef _COMPUTER_
#define _COMPUTER_

#include "Player.h"
#include <cstdlib>
#include <time.h>
#include <stack>

class Computer : public Character
{
	int** enemy_placement;
	Ship* enemy_ships[5];
	Player* player;

	//Fighting System
	int directions[4];  // 0 if not tested, 1 if true, -1 otherwise
	int direction;		// 0 West, 1 South, 2 East, 3 North
	std::stack<Vector2i> initial_hit, unfinished_ships;

public:
	Computer(RenderWindow& window, Grid* grid);
	~Computer();

	//Preparation Phase
	void PrepPhase();
	void Randomizer();
	void PickRotation(Ship*);
	void PickPosition(Ship*);
	void PickMovement(Ship*);

	//Gameplay Phase
	void PickTarget(Vector2i&);
	bool CheckShips(Vector2i&);
	int CheckArea(Vector2i&);
	bool UpdateHitStack(Vector2i&);
	void ChooseDirection();
	bool FinishShips(Vector2i&);
	bool ValidPath(Vector2i&);

	//setters
	void setEnemyInfo(Player*);
	void setInitialHit(Vector2i pos);
};


#endif