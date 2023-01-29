#include "Character.h"

Character::Character(RenderWindow& window, Grid* grid)
{
	game_window = &window;
	player_grid = grid;
	state = alive;
	
	//set placement grid to empty by default
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			placement[i][j] = 0;
}

bool Character::setPlacements(vector<Vector2i> hitbox)
{
	for (int i = 0; i < hitbox.size(); i++)
	{
		int x = hitbox[i].x, y = hitbox[i].y;
		if (placement[x][y] == -1)
			return false;
		placement[x][y] = -1;
	}
	return true;
}

void Character::resetPlacements()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			placement[i][j] = 0;
		}
	}
}
//void Character::setGameSystem(GameSystem& game)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		player_ships[i]->setGameSystem(game);
//	}
//}