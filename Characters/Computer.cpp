#include "Computer.h"

Computer::Computer(RenderWindow& window, Grid* grid) : Character(window, grid)
{
	srand(time(0));
	player_ships[0] = new Carrier(window);
	player_ships[1] = new Battleship(window);
	player_ships[2] = new Cruiser(window);
	player_ships[3] = new Submarine(window);
	player_ships[4] = new Warship(window);
}

Computer::~Computer()
{
	for (int i = 0; i < 5; i++)
	{
		delete player_ships[i];
	}
}

void Computer::draw()
{

}

void Computer::PrepPhase()
{
	Randomizer();
}

void Computer::Randomizer()
{
	bool first = true, second = true;
	for (int i = 0; i < 5;)
	{
		switch (abs(rand()) % 3)
		{
		case 0: PickRotation(player_ships[i]); first = false; break;
		case 1: PickPosition(player_ships[i]); second = false; break;
		case 2: PickMovement(player_ships[i]); break;
		}
		if (!first && !second)
			i++;
	}
}

void Computer::PickRotation(Ship* s)
{
	switch (abs(rand()) % 2)
	{
	case 0: s->setRotation(horizontal); break;
	case 1: s->setRotation(vertical); break;
	}
}

void Computer::PickPosition(Ship* s)
{
	if (!s->setColumn(abs(rand()) % 10))
		PickPosition(s);
	if (!s->setRow((rand()) % 10))
		PickPosition(s);
}

void Computer::PickMovement(Ship* s)
{
	switch (abs(rand()) % 5)
	{
	case 0: s->MoveUp(); break;
	case 1: s->MoveDown(); break;
	case 2: s->MoveLeft(); break;
	case 3: s->MoveRight(); break;
	case 4: s->Rotate(); break;
	}
}

void Computer::PickTarget(Vector2i& pos)
{
	do
	{
		pos.x = abs(rand()) % 10; pos.y = abs(rand()) % 10;
		
	} while (!CheckShips(pos));
	if (!player->ShotTracker(pos))
		PickTarget(pos);
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				enemy_placement[i][j] = player->getPlacement(i, j);
			}
		}
	}
}

bool Computer::CheckShips(Vector2i& pos)
{
	if (CheckArea(pos, 5, 4) && enemy_ships[0]->getHealth() == alive)
	{
		cout << "Can store Carrier\n";
		return true;
	}
	if (CheckArea(pos, 4, 14) && enemy_ships[1]->getHealth() == alive)
	{
		cout << "Can store Battlefield\n";
		return true;
	}
	if (CheckArea(pos, 3, 24) && enemy_ships[2]->getHealth() == alive)
	{
		cout << "Can store Cruiser\n";
		return true;
	}
	if (CheckArea(pos, 3, 34) && enemy_ships[3]->getHealth() == alive)
	{
		cout << "Can store Sub\n";
		return true;
	}
	if (CheckArea(pos, 2, 44) && enemy_ships[4]->getHealth() == alive)
	{
		cout << "Can store Warship\n";
		return true;
	}
	return false;
}

bool Computer::CheckArea(Vector2i& pos, int size, int range)
{
	int x = pos.x; int y = pos.y;
	int n = 0, i;
	bool passed = false;
	for (i = 0; i < 10; i++)
	{
		n++;
		if (i == y)
			passed = true;
		if (passed && n > size)
			return true;
		if (enemy_placement[x][i] == -1 && !passed)
			n = 0;
		else if (enemy_placement[x][i] == -1 && passed && n <= size)
			break;
	}
	n = 0;
	passed = false;
	for (i = 0; i < 10; i++)
	{
		n++;
		if (i == x)
			passed = true;
		if (passed && n > size)
			return true;
		if (enemy_placement[i][y] == -1 && !passed)
			n = 0;
		if (enemy_placement[i][y] == -1 && passed && n <= size)
			return false;
		
	}
	return false;
}

void Computer::setEnemyInfo(Player* p)
{
	player = p;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			enemy_placement[i][j] = p->getPlacement(i, j);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		enemy_ships[i] = p->getShip(i);
	}
}