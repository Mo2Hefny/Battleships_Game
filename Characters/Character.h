#ifndef _CHARACTER_
#define _CHARACTER_

#include "../DEFS.h"
#include "../UI/Grid.h"
#include "../Ships/Carrier.h"
#include "../Ships/Battleship.h"
#include "../Ships/Cruiser.h"
#include "../Ships/Submarine.h"
#include "../Ships/Warship.h"

class Character
{
protected:
	PlayerState state;
	int placement[10][10];
	Grid* player_grid;
	RenderWindow* game_window;
	Ship* player_ships[5];

public:
	Character() {}
	Character(RenderWindow& window, Grid* grid);

	void resetPlacements();

	//setters
	bool setPlacements(vector<Vector2i>);
	//void setGameSystem(GameSystem& game);

	//getters
	int (*(getPlacement)())[10] { return placement; }
	Ship* getShip(int index) { return player_ships[index]; }

};

#endif