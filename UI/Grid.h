#ifndef GRID
#define GRID

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"

using namespace std;
using namespace sf;

class Grid
{
	int** placement, shot_count, hit, miss;
	RectangleShape grid[10][10];
	CircleShape* shots[100];
	RenderWindow* game_window;
public:
	Grid();
	~Grid();

	// Preparation Phase
	void resetPlacements();
	int CheckValidity();

	// Gameplay Phase
	int HitGrid(Vector2i&);

	void draw(int);
	void ColorShip(Color& c, vector<Vector2i>&);

	// setters
	void setPlacements(vector<Vector2i>, int);
	void setWindow(RenderWindow& window) { game_window = &window; }

	// getters
	int**& getPlacements() { return placement; }
};

#endif