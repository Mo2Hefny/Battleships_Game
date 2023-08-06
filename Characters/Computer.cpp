#include "Computer.h"

Computer::Computer(RenderWindow& window, Grid* grid) : Character(window, grid)
{
	srand(time(0));
	character_ships[0] = new Carrier();
	character_ships[1] = new Battleship();
	character_ships[2] = new Cruiser();
	character_ships[3] = new Submarine();
	character_ships[4] = new Warship();
	for (auto& direction : directions)	direction = 0;
}

Computer::~Computer()
{
	for (int i = 0; i < 5; i++)
	{
		delete character_ships[i];
	}
}

//======================================================================================//
//								Preparation Phase										//
//======================================================================================//

void Computer::PrepPhase()
{
	Randomizer();
}

void Computer::Randomizer()
{
	bool first = true, second = true;
	for (int i = 0; i < 5;)
	{
		Ship* ship = character_ships[i];
		switch (abs(rand()) % 3)
		{
		case 0: PickRotation(ship); first = false; break;
		case 1: PickPosition(ship); second = false; break;
		case 2: PickMovement(ship); break;
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

//======================================================================================//
//								  Gameplay Phase		   								//
//======================================================================================//

void Computer::PickTarget(Vector2i& pos)
{
	do
	{
		pos.x = abs(rand()) % 10; pos.y = abs(rand()) % 10;
		
	} while (!CheckShips(pos));
	if (!player->ShotTracker(pos))
		PickTarget(pos);
}

bool Computer::CheckShips(Vector2i& pos)
{
	int space_available = CheckArea(pos);
	if (space_available == 5 && enemy_ships[0]->getHealth() == alive)
	{
		cout << "Can store Carrier\n";
		return true;
	}
	if (space_available >= 4 && enemy_ships[1]->getHealth() == alive)
	{
		cout << "Can store Battlefield\n";
		return true;
	}
	if (space_available >= 3 && enemy_ships[2]->getHealth() == alive)
	{
		cout << "Can store Cruiser\n";
		return true;
	}
	if (space_available >= 3  && enemy_ships[3]->getHealth() == alive)
	{
		cout << "Can store Sub\n";
		return true;
	}
	if (space_available >= 2 && enemy_ships[4]->getHealth() == alive)
	{
		cout << "Can store Warship\n";
		return true;
	}
	return false;
}

int Computer::CheckArea(Vector2i& pos)
{
	int x = pos.x; int y = pos.y;
	int n = 5, res = 0;
	int i;
	for (i = max(y - 5, 0); i < min(y + 5, 10); i++)
	{
		int block = enemy_placement[i][x];
		if (block == -1)
			n = min(n, abs(y - i));
	}
	res = max(res, n);
	n = 5;
	for (i = max(x - 5, 0); i < min(x + 5, 10); i++)
	{
		int block = enemy_placement[y][i];
		if (block == -1)
			n = min(n, abs(y - i));
	}
	return max(res, n);
}

bool Computer::ValidPath(Vector2i& pos)
{
	int x = pos.x + dx[direction];
	int y = pos.y + dy[direction];
	return !(x < 0 || y < 0 || x >= 10 || y >= 10 || !~directions[direction]);
}

bool Computer::UpdateHitStack(Vector2i& pos)
{
	int cnt = 4;
	do {
		for (int i = 0; i < 4; i++)
		{
			int x = pos.x + dx[i];
			int y = pos.y + dy[i];
			if (x < 0 || y < 0 || x >= 10 || y >= 10)	// if stopped by border
			{
				directions[i] = -1;

				// Switch path direction to the opposite side
				if (direction == i)
					direction = (direction + 2) % 4;
			}
			else if (enemy_placement[y][x] < 0)	// if position was already attacked
			{
				directions[i] = -1;
				cnt--;
			}
			else directions[i] = 0;
		}
		if (!cnt)
		{
			initial_hit.pop();
			pos = initial_hit.top();
		}
	} while (!cnt && !initial_hit.empty());
	return cnt;
}

void Computer::ChooseDirection()
{
	do
	{
		direction = abs(rand()) % 4;
	} while (!~directions[direction]);
}

bool Computer::FinishShips(Vector2i& pos)
{
	if (initial_hit.empty())
	{
		if (unfinished_ships.empty())
		return false;
		while (!unfinished_ships.empty())
		{
			initial_hit.push(unfinished_ships.top());
			unfinished_ships.pop();
		}
	}
	Vector2i p, mainpoint;
	do {
		mainpoint = initial_hit.top();
		if (enemy_placement[mainpoint.y][mainpoint.x] == -2)
		{
			direction = -1;
			initial_hit.pop();
		}
		if (initial_hit.empty() && !unfinished_ships.empty())
		{
			initial_hit.push(unfinished_ships.top());
			unfinished_ships.pop();
		}
	} while (enemy_placement[mainpoint.y][mainpoint.x] == -2 && !initial_hit.empty());
	if (initial_hit.empty()) return false;

	if (!~direction || !ValidPath(mainpoint)) // No chosen path or it is invalid
	{
		if (!UpdateHitStack(mainpoint))	return false;
		ChooseDirection();
	}
	
	// Chose a path.
	pos.x = mainpoint.x + dx[direction];
	pos.y = mainpoint.y + dy[direction];

	if (enemy_placement[pos.y][pos.x] == 1)
	{
		initial_hit.push(pos);
	}
	else
	{
		directions[direction] = -1;
		direction = (direction + 2) % 4;	// Switch direction on hitting an empty space
		if (!~directions[direction])
		{
			direction = -1;
			return true;
		}
		int res;
		do {
			unfinished_ships.push(mainpoint);
			initial_hit.pop();
			if (initial_hit.empty()) return true;
			mainpoint = initial_hit.top();
			int x = mainpoint.x + dx[direction];
			int y = mainpoint.y + dy[direction];
			if (x < 0 || y < 0 || x >= 10 || y >= 10)
			{
				res = -2;
				break;
			}
			res = enemy_placement[y][x];
		} while (!~ res);
		if (res == -2)
		{
			directions[direction] = -1;
		}
	}
	return true;
}

void Computer::setEnemyInfo(Player* p)
{
	player = p;
	enemy_placement = p->getPlacement();
	for (int i = 0; i < 5; i++)
	{
		enemy_ships[i] = p->getShip(i);
	}
}

void Computer::setInitialHit(Vector2i pos)
{
	int x = pos.x, y = pos.y;

	// Invalid input
	if (enemy_placement[y][x] == -2)
	{
		cout << "Error\n";
		exit(1);
	}
	initial_hit.push(pos);
}