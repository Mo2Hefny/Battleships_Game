#include "Character.h"

Character::Character(RenderWindow& window, Grid* grid):placement(grid->getPlacements())
{
	game_window = &window;
	character_grid = grid;
	state = alive;
	
	//set placement grid to empty by default
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			placement[i][j] = 0;
}

bool Character::ShotTracker(Vector2i pos)
{
	int x = pos.x; int y = pos.y;
	if (placement[y][x] < 0)
		return false;

	UI_s.shotL.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(_WAIT_));

	return true;
}

void Character::CheckShipsHealth()
{
	int j, count = 0;

	for (int i = 0; i < 5; i++)
	{
		if (character_ships[i]->getHealth() == dead)
		{
			count++;
			continue;
		}
		vector<Vector2i> temp = character_ships[i]->getHitbox();
		for (j = 0; j < temp.size(); j++)
		{
			int x = temp[j].x; int y = temp[j].y;
			if (placement[y][x] == 1)
				break;
		}
		if (j == temp.size())
		{
			count++;
			character_ships[i]->setHealth(dead);
			character_ships[i]->changeHitboxValues(-2, placement);
			cout << "Ship Destroyed.\n";
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
		vector<Vector2i> temp = character_ships[i]->getHitbox();
		for (int j = 0; j < temp.size(); j++)
		{
			int x = temp[j].x; int y = temp[j].y;
			placement[y][x] = 1;
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