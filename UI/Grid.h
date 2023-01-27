#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"
using namespace std;
using namespace sf;

class Grid
{
	RectangleShape grid[10][10];
public:
	Grid();
	void draw(RenderWindow &game, Player p);
};

#endif