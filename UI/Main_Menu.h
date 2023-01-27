#ifndef MENU
#define MENU

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define Max_Menu_Options 3
#define	_WIDTH_	1280
#define _HEIGHT_ 720

class MainMenu {
	int MainMenuSelected;
	Font font;
	Text MenuText[Max_Menu_Options];
	RenderWindow* Menu;
	Texture Background_img, PBackground_img, OBackground_img;
public:
	MainMenu(int width, int height, RenderWindow& window);
	void Execute();
	void draw();
	void MoveUp();
	void MoveDown();
	int CurrentSelected() const { return MainMenuSelected;  }
};

#endif