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
	int** placement;
	Grid* character_grid;
	RenderWindow* game_window;
	Ship* character_ships[5];

public:
	Character(RenderWindow& window, Grid* grid);
	virtual ~Character() {}

	void resetPlacements();
	bool ShotTracker(Vector2i);
	void CheckShipsHealth();

	//setters
	void setPlacements();
	//void setGameSystem(GameSystem& game);

	//getters
	int** getPlacement() { return placement; }
	PlayerState getState() const { return state; }
	Ship* getShip(int index) const { return character_ships[index]; }

};

#endif