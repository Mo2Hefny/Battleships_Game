#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"
#include "../GameManager/GameSystem.h"
#include "Options.h"

using namespace std;
using namespace sf;

#define Max_Menu_Options 3

class MainMenu {
	int MainMenuSelected;
	Font font;
	Text MenuText[Max_Menu_Options];
	RenderWindow* Menu;
	Texture Background_img, PBackground_img, OBackground_img;
	GameSystem* Game;
	Options* options;

public:
	MainMenu(int width, int height, RenderWindow& window);
	void Execute();
	void draw();
	void MoveUp();
	void MoveDown();
	void Switch();
	bool OnText() const;
	int CurrentSelected() const { return MainMenuSelected;  }
};

#endif