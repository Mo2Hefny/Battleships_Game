#ifndef _GAME_SYSTEM_
#define _GAME_SYSTEM_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Characters/Player.h"
#include "../Characters/Computer.h"
#include "../UI/Options.h"

using namespace std;
using namespace sf;

class Player;
class Computer;
class GameSystem
{
	int MenuSelected;
	RenderWindow* game_window;
	PlayState mode;
	Player* player;
	Computer* computer;
	Options* settings;
	Grid grid[2];

	//UI
	Font font;
	Text Players_name[2], prep_ships, status_bar_msg, menuOpT[4], endgameTxt;
	Texture PBackground_img, carrierT, battleshipT, cruiserT, subT, warshipT, status_barT, menu_dropT;
	RectangleShape PBackground, Sections[3], Underline[3], popup, menuOp[4], endgameUnderline;
	Sprite carrier, battleship, cruiser, sub, warship, status_bar, menu_drop;

public:
	GameSystem(RenderWindow& window, Options*);
	~GameSystem();
	void Execute();
	void draw();
	

	//Preparation Phase
	void PrepUI();
	void PrepPhase();
	void PrepComputer();
	void SelectedShip();
	void UpdateGrid(Color& , vector<Vector2i>&, TeamOpt = player1);

	//GamePlay
	void GamePhase();
	Vector2i getGridPos();
	int CheckWinner();
	void GameComputer(Vector2i& pos);

	//Menu
	bool OpenedMenu();
	void OpenMenu();
	void FinishMenu(TeamOpt);
	void MoveUp();
	void MoveDown();
	void PrepMenu();
	void Switch();
	int CurrentSelected() const { return MenuSelected; }
	int OnText() const;
	
	//setters
	void setMode(PlayState state) { mode = state; }
	void setString(string s) { status_bar_msg.setString(s); }

	//getters
	PlayState CurrentMode() const { return mode; }
	

};

#endif