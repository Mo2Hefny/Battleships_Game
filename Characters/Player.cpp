#include "Player.h"

Player::Player(RenderWindow& window, Grid* grid) : Character(window, grid)
{
	selected_ship = NULL;
	character_ships[0] = new Carrier();
	character_ships[1] = new Battleship();
	character_ships[2] = new Cruiser();
	character_ships[3] = new Submarine();
	character_ships[4] = new Warship();
}

Player::~Player()
{
	for (int i = 0; i < 5; i++)
	{
		delete character_ships[i];
	}
}

void Player::setSelected(char c)
{
	switch (c)
	{
	case 'C':
		selected_ship = character_ships[0];
		break;
	case 'B':
		selected_ship = character_ships[1];
		break;
	case 'c':
		selected_ship = character_ships[2];
		break;
	case 'S':
		selected_ship = character_ships[3];
		break;
	case 'W':
		selected_ship = character_ships[4];
		break;
	default:
		selected_ship = NULL;
		break;
	}
}

int Player::getDeadCount() const
{
	int count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (character_ships[i]->getHealth() == dead)
			count++;
	}
	return count;
}