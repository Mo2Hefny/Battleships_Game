#include "Player.h"

Player::Player(RenderWindow& window, Grid* grid) : Character(window, grid)
{
	selected_ship = NULL;
	player_ships[0] = new Carrier(window);
	player_ships[1] = new Battleship(window);
	player_ships[2] = new Cruiser(window);
	player_ships[3] = new Submarine(window);
	player_ships[4] = new Warship(window);
}

Player::~Player()
{
	for (int i = 0; i < 5; i++)
	{
		delete player_ships[i];
	}
}

void Player::draw()
{
	game_window->draw(player_ships[0]->getSprite());
	//game_window->display();
}

void Player::setSelected(char c)
{
	switch (c)
	{
	case 'C':
		selected_ship = player_ships[0];
		break;
	case 'B':
		selected_ship = player_ships[1];
		break;
	case 'c':
		selected_ship = player_ships[2];
		break;
	case 'S':
		selected_ship = player_ships[3];
		break;
	case 'W':
		selected_ship = player_ships[4];
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
		if (player_ships[i]->getHealth() == dead)
			count++;
	}
	return count;
}