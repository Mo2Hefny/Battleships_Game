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
	RenderWindow* game_window;
public:
	Grid();
	bool CheckValidity(Color c);
	void draw(int player);
	bool ColorShip(RenderWindow& window, Color& c, vector<Vector2i>&);

	//setters
	void setWindow(RenderWindow& window) { game_window = &window; }
};

#endif