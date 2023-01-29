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
	RenderWindow* game_window;
	PlayState mode;
	Player* player;
	Computer* computer;
	Grid grid[2];

	//UI
	Font font;
	Text Players_name[2], prep_ships, status_bar_msg;
	Texture PBackground_img, carrierT, battleshipT, cruiserT, subT, warshipT, status_barT;
	RectangleShape PBackground, Sections[3], Underline[3];
	Sprite carrier, battleship, cruiser, sub, warship, status_bar;

public:
	GameSystem(int width, int height, RenderWindow& window);
	void Execute();
	void draw();
	void PrepPhase();
	void PrepUI();
	void PrepComputer();
	void SelectedShip();
	void UpdateGrid(Color& , vector<Vector2i>&, int = 0);
	PlayState CurrentMode() const { return mode; }
	
	//setters
	void setMode(PlayState state) { mode = state; }
	void setString(string s) { status_bar_msg.setString(s); }

	//getters
	

};

#endif