#ifndef _GAME_SYSTEM_
#define _GAME_SYSTEM_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Characters/Player.h"
#include "../Characters/Computer.h"

using namespace std;
using namespace sf;

class Player;
class Computer;
class GameSystem
{
	PlayState mode;
	Font font;
	RenderWindow* game_window;
	Texture PBackground_img;
	RectangleShape PBackground, Sections[3];
	Text Players_name[2], prep_ships;
	Player* player;
	Computer* computer;
	Grid grid[2];
	//Ships
	Texture carrierT, battleshipT, cruiserT, subT, warshipT;
	Sprite carrier, battleship, cruiser, sub, warship;
	Vector2i sprite_pos[5];
	float width[5], height[5];
public:
	GameSystem(int width, int height, RenderWindow& window);
	void Execute();
	void draw();
	void PrepPhase();
	void PrepUI();
	void SelectedShip();
	bool UpdateGrid(Color& , vector<Vector2i>&, int = 0);
	PlayState CurrentMode() const { return mode; }
	
	//setters
	void setMode(PlayState state) { mode = state; }

};

#endif