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
	int direction;		// 0 West, 1 North, 2 East, 3 South
	int spotted, total_spotted;
	std::stack<Vector2i> initial_hit, unfinished_ships;
	Vector2i* currTarget, path;


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
	void updateEnemyShips();
	bool FinishShips(Vector2i&);
	bool UpdatePath(Vector2i&);
	bool TestHitPath(Vector2i&);
	void MoveInPath(Vector2i&);

	//getters
		
	//setters
	void setEnemyInfo(Player*);
	void setHitPath(Vector2i);
	void setInitialHit(Vector2i pos);
};


#endif