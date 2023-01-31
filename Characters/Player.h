#ifndef _PLAYER_
#define _PLAYER_

#include "Character.h"

class Player : public Character
{
	Ship* selected_ship;
public:
	Player(RenderWindow& window, Grid* grid);
	~Player();
	void draw();

	//getters
	Ship* getSelected() const { return selected_ship; }
	int getDeadCount() const;

	//setters
	void setSelected(char);
};

#endif