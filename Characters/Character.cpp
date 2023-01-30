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

bool Character::ShotTracker(Vector2i pos)
{
	int x = pos.x; int y = pos.y;
	if (placement[x][y] == -1) 
		return false;
	if (placement[x][y] >= 44 && placement[x][y] <= 48)
		return false;
	if (placement[x][y] >= 64 && placement[x][y] <= 67)
		return false;
	if (placement[x][y] >= 84 && placement[x][y] <= 86)
		return false;
	if (placement[x][y] >= 104 && placement[x][y] <= 106)
		return false;
	if (placement[x][y] >= 124 && placement[x][y] <= 125)
		return false;

	UI_s.shotL.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(_WAIT_));

	if (placement[x][y] == 0)
		placement[x][y] = -1;
	else
	{
		UI_s.explosion.play();
		placement[x][y] -= 6;
	}
	CheckShipsHealth();
	return true;
}

void Character::CheckShipsHealth()
{
	int n, j, count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (player_ships[i]->getHealth() == dead)
		{
			count++;
			continue;
		}
		n = 50 + i * 20;
		vector<Vector2i> temp = player_ships[i]->getHitbox();
		for (j = 0; j < temp.size(); j++)
		{
			int x = temp[j].x; int y = temp[j].y;
			if (placement[x][y] == n++)
				break;
		}
		if (j == temp.size())
		{
			count++;
			player_ships[i]->setHealth(dead);
			UI_s.explosion.stop();
			UI_s.explosion_ship.play();
		}
	}
	if (count == 5)
		state = dead;
}

void Character::setPlacements()
{
	int n;
	for (int i = 0; i < 5; i++)
	{
		n = 50 + i * 20;
		vector<Vector2i> temp = player_ships[i]->getHitbox();
		for (int j = 0; j < temp.size(); j++)
		{
			int x = temp[j].x; int y = temp[j].y;
			placement[x][y] = n++;
		}
	}
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