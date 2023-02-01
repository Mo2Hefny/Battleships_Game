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

	//Fighting System
	int north, east, south, west;  // 0 if not tested, 1 if true, -1 otherwise
	int spotted, total_spotted;
	Vector2i initial_hit[5], path;


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
	bool CheckArea(Vector2i&, int);
	void updateEnemyPlacements();
	bool FinishShips(Vector2i&);
	bool TestHitPath(Vector2i&);
	void MoveInPath(Vector2i&);

	//getters
	Vector2i getInitialHit(int i) const { return initial_hit[(i > 4) ? 4 : i]; }
		
	//setters
	void setEnemyInfo(Player*);
	void setHitPath(Vector2i);
	void setInitialHit(Vector2i pos) { initial_hit[total_spotted++] = pos; }
};


#endif