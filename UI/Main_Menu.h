#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../GameManager/GameSystem.h"
#include "Options.h"

using namespace std;
using namespace sf;

#define Max_Menu_Options 3

class MainMenu {
	int MainMenuSelected;
	
	//Text info
	Font font;
	Text MenuText[Max_Menu_Options];
	Vector2i item_pos[Max_Menu_Options];
	float width[3], height[3];

	RenderWindow* Menu;
	Texture Background_img;
	GameSystem* Game;
	Options* options;

public:
	MainMenu(RenderWindow& window);
	~MainMenu();
	void Execute();
	void draw();
	void MoveUp();
	void MoveDown();
	void Switch();
	void Load();
	int OnText() const;
	int CurrentSelected() const { return MainMenuSelected;  }
};

#endif