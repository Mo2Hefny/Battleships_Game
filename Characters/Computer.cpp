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
	cout << "Preping computer\n";
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