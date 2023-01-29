#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"

using namespace std;
using namespace sf;

class Grid
{
	int placement[10][10];
	RectangleShape grid[10][10];
	RenderWindow* game_window;
public:
	Grid();
	int CheckValidity();
	void draw(int player);
	void ColorShip(Color& c, vector<Vector2i>&);
	void resetPlacements();

	//setters
	void setPlacements(vector<Vector2i>, int);
	void setWindow(RenderWindow& window) { game_window = &window; }
};

#endif