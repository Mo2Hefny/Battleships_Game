#ifndef PLAY
#define PLAY

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"
#include "../UI/Grid.h"
using namespace std;
using namespace sf;

class GameSystem
{
	PlayState mode;
	Font font;
	RenderWindow* Menu;
	Texture PBackground_img;
	RectangleShape PBackground;
	Text Players_name[2];
	Grid grid[2];
public:
	GameSystem(int width, int height, RenderWindow& window);
	void Execute();
	void draw();
	void PrepGrid();
	void MoveDown();
	PlayState CurrentMode() const { return mode; }
	
	//setters
	void setMode(PlayState state) { mode = state; }

};

#endif