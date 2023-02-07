#include "Computer.h"

Computer::Computer(RenderWindow& window, Grid* grid) : Character(window, grid)
{
	srand(time(0));
	player_ships[0] = new Carrier();
	player_ships[1] = new Battleship();
	player_ships[2] = new Cruiser();
	player_ships[3] = new Submarine();
	player_ships[4] = new Warship();
	north = east = south = west = spotted = total_spotted = 0;

	//initialize positions for AI
	for (int i = 0; i < 5; i++)
	{
		initial_hit[i].x = -1;
	}
	
	spotted = -1;
}

Computer::~Computer()
{
	for (int i = 0; i < 5; i++)
	{
		delete player_ships[i];
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
	else
	{
		updateEnemyPlacements();
	}
}

void Computer::updateEnemyPlacements()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			enemy_placement[i][j] = player->getPlacement(i, j);
		}
	}
}

void Computer::updateEnemyShips()
{
	for (int i = 0; i < 5; i++)
	{
		if (enemy_ships[i]->getHealth() == dead)
		{
			initial_hit[i].x = -1;
		}
	}
}

bool Computer::CheckShips(Vector2i& pos)
{
	if (CheckArea(pos, 5) && enemy_ships[0]->getHealth() == alive)
	{
		//cout << "Can store Carrier\n";
		return true;
	}
	if (CheckArea(pos, 4) && enemy_ships[1]->getHealth() == alive)
	{
		//cout << "Can store Battlefield\n";
		return true;
	}
	if (CheckArea(pos, 3) && enemy_ships[2]->getHealth() == alive)
	{
		//cout << "Can store Cruiser\n";
		return true;
	}
	if (CheckArea(pos, 3) && enemy_ships[3]->getHealth() == alive)
	{
		//cout << "Can store Sub\n";
		return true;
	}
	if (CheckArea(pos, 2) && enemy_ships[4]->getHealth() == alive)
	{
		//cout << "Can store Warship\n";
		return true;
	}
	return false;
}

bool Computer::CheckArea(Vector2i& pos, int size)
{
	int x = pos.x; int y = pos.y;
	int n = 0, i;
	bool passed = false;
	for (i = 0; i < 10; i++)
	{
		n++;
		int range = enemy_placement[x][i];
		if (i == y)
			passed = true;
		if (passed && n > size)
			return true;
		
		if ((range == -1 || range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125) && !passed)
			n = 0;
		else if ((range == -1 || range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125) && passed && n <= size)
			break;
	}
	n = 0;
	passed = false;
	for (i = 0; i < 10; i++)
	{
		n++;
		int range = enemy_placement[i][y];
		if (i == x)
			passed = true;
		if (passed && n > size)
			return true;
		if ((range == -1 || range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125) && !passed)
			n = 0;
		if ((range == -1 || range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125) && passed && n <= size)
			return false;
		
	}
	return false;
}

bool Computer::FinishShips(Vector2i& pos)
{

	if (spotted == -1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (initial_hit[i].x != -1)
			{
				cout << "Found Ship.\n";
				spotted = i;
				break;
			}
		}
	}
	if (spotted == -1)
	{
		return false;
	}

	Vector2i mainpoint = getInitialHit(spotted);
	Vector2i p;

	if (north == -1 && south == -1 && east == -1 && west == -1 || initial_hit[spotted].x == -1)
	{
		spotted = -1;
		north = east = south = west = 0;
		FinishShips(pos);
	}
	else
	{
	
		if (north != 1 && south != 1 && east != 1 && west != 1)
		{
			do
			{
				path = mainpoint;
				setHitPath(mainpoint);
			} while (!TestHitPath(path));
			p = path;
		}
		else
		{
			p = path;

			// Moves north
			if (north == 1 && path.x > 0)
			{
				path.x--;
			}
			else if (north == 1 && path.x <= 0)		// Changes direction if hit borber.
			{
				north = -1;
				if (south == 0)
				{
					south = 1;
					path = mainpoint;
					path.x++;
				}
			}
			// Moves south
			else if (south == 1 && path.x < 9)
			{
				path.x++;
			}
			else if (south == 1 && path.x >= 9)		// Changes direction if hit borber.
			{
				south = -1;
				if (north == 0)
				{
					north = 1;
					path = mainpoint;
					path.x--;
				}
			}
			// Moves east
			else if (east == 1 && path.y < 9)
			{
				path.y++;
			}
			else if (east == 1 && path.y >= 9)		// Changes direction if hit borber.
			{
				east = -1;
				if (west == 0)
				{
					west = 1;
					path = mainpoint;
					path.y--;
				}
			}
			// Moves west
			else if (west == 1 && path.y > 0)
			{
				path.y--;
			}
			else if (west == 1 && path.y <= 0)		// Changes direction if hit borber.
			{
				west = -1;
				if (east == 0)
				{
					east = 1;
					path = mainpoint;
					path.y++;
				}
			}
		}
		while (!TestHitPath(path))
		{
			path = p;
			setHitPath(mainpoint);
		}

		p = path;
		MoveInPath(p);

		pos = p;
		return true;
	}
}

void Computer::setHitPath(Vector2i pos)
{
	switch (abs(rand()) % 4)
	{
	case 0:
		if (north == -1)
		{
			setHitPath(pos);
		}
		else if (pos.x > 0)
		{
			north = 1;
			path.x--;
			cout << "selected north\n";
		}
		else
		{
			cout << "north is not reachable\n";
			north = -1;
			setHitPath(pos);
		}
		break;
	case 1:
		if (east == -1)
		{
			setHitPath(pos);
		}
		else if (pos.y < 9)
		{
			east = 1;
			path.y++;
			cout << "selected east\n";
		}
		else
		{
			cout << "east is not reachable\n";
			east = -1;
			setHitPath(pos);
		}
		break;

	case 2:
		if (south == -1)
		{
			setHitPath(pos);
		}
		else if (pos.x < 9)
		{
			south = 1;
			path.x++;
			cout << "selected south\n";
		}
		else
		{
			cout << "south is not reachable\n";
			south = -1;
			setHitPath(pos);
		}
		break;

	case 3:
		if (west == -1)
		{
			setHitPath(pos);
		}
		else if (pos.y > 0)
		{
			west = 1;
			path.y--;
			cout << "selected west\n";
		}
		else
		{
			cout << "west is not reachable\n";
			west = -1;
			setHitPath(pos);
		}
		break;
	}
}

bool Computer::TestHitPath(Vector2i& path)
{
	int x = path.x, y = path.y;
	if (enemy_placement[x][y] == -1)
		return false;
	if (enemy_placement[x][y] >= 44 && enemy_placement[x][y] <= 48)
		return false;
	if (enemy_placement[x][y] >= 64 && enemy_placement[x][y] <= 67)
		return false;
	if (enemy_placement[x][y] >= 84 && enemy_placement[x][y] <= 86)
		return false;
	if (enemy_placement[x][y] >= 104 && enemy_placement[x][y] <= 106)
		return false;
	if (enemy_placement[x][y] >= 124 && enemy_placement[x][y] <= 125)
		return false;
	return true;
}

void Computer::MoveInPath(Vector2i& pos)
{
	int x = path.x, y = path.y;
	int range = enemy_placement[x][y] - 6;
	int type = enemy_placement[getInitialHit(spotted).x][getInitialHit(spotted).y];

	if (north == 1)
	{
		if (enemy_placement[x][y] == 0)
		{
			if (abs(x - getInitialHit(spotted).x) > 1 && !south && getInitialHit(spotted).x < 9)
			{
				south = 1;
				path = getInitialHit(spotted);
			}
			north = -1;
			return;
		}
		else if (range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125)
		{
			if (abs(type - range) < 5)
			{
				return;
			}
			else
			{
				setInitialHit(path);
				return;
			}
		}
	}
	else if (south == 1)
	{
		if (enemy_placement[x][y] == 0)
		{
			if (abs(x - getInitialHit(spotted).x) > 1 && !north && getInitialHit(spotted).x > 0)
			{
				north = 1;
				path = getInitialHit(spotted);
			}
			south = -1;
			return;
		}
		else if (range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125)
		{
			if (abs(type - range) < 5)
			{
				return;
			}
			else
			{
				setInitialHit(path);
				return;
			}
		}
	}
	else if (east == 1)
	{
		if (enemy_placement[x][y] == 0)
		{
			if (abs(y - getInitialHit(spotted).y) > 1 && !west && getInitialHit(spotted).y > 0)
			{
				west = 1;
				path = getInitialHit(spotted);
			}
			east = -1;
			return;
		}
		else if (range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125)
		{
			if (abs(type - range) < 5)
			{
				return;
			}
			else
			{
				setInitialHit(path);
				return;
			}
		}
	}
	else if (west == 1)
	{
		if (enemy_placement[x][y] == 0)
		{
			if (abs(y - getInitialHit(spotted).y) > 1 && !east && getInitialHit(spotted).x < 9)
			{
				east = 1;
				path = getInitialHit(spotted);
			}
			west = -1;
			return;
		}
		else if (range >= 44 && range <= 48 || range >= 64 && range <= 67 || range >= 84 && range <= 86 || range >= 104 && range <= 106 || range >= 124 && range <= 125)
		{
			if (abs(type - range) < 5)
			{
				return;
			}
			else
			{
				setInitialHit(path);
				return;
			}
		}
	}
	else
		cout << "!!!!ERROR!!!!\n";
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

void Computer::setInitialHit(Vector2i pos)
{
	int x = pos.x, y = pos.y;

	// Invalid input
	if (enemy_placement[x][y] <= 0)
	{
		cout << "Error\n";
		exit(1);
	}
	// Carrier Spotted
	else if (enemy_placement[x][y] <= 60 && enemy_ships[0]->getHealth() == alive)
	{
		//cout << "Carrier spotted!\n";
		initial_hit[0] = pos;
	}
	// Battleship Spotted
	else if (enemy_placement[x][y] <= 80 && enemy_ships[1]->getHealth() == alive)
	{
		//cout << "Battleship spotted!\n";
		initial_hit[1] = pos;
	}
	// Cruiser Spotted
	else if (enemy_placement[x][y] <= 100 && enemy_ships[2]->getHealth() == alive)
	{
		//cout << "Cruiser spotted!\n";
		initial_hit[2] = pos;
	}
	// Submarine Spotted
	else if (enemy_placement[x][y] <= 120 && enemy_ships[3]->getHealth() == alive)
	{
		//cout << "Sub spotted!\n";
		initial_hit[3] = pos;
	}
	// Warship Spotted
	else if (enemy_placement[x][y] <= 140 && enemy_ships[4]->getHealth() == alive)
	{
		//cout << "Warship spotted!\n";
		initial_hit[4] = pos;
	}

}