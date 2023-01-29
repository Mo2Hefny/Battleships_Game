#ifndef _DEF_
#define _DEF_

#include <SFML/Graphics.hpp>
#include <iostream>

#define	_WIDTH_	1600	
#define _HEIGHT_ 900

using namespace sf;

enum PlayState
{
	prep,
	game,
	closed
};

enum PlayerState
{
	dead,
	alive
};

enum OptionMenu
{
	sound,

	closed_op
};

enum Direction
{
	horizontal,
	vertical
};

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Settings
{
	Vector2i* player1 = new Vector2i(80, 220);
	Vector2i* player2 = new Vector2i(560, 220);
	Vector2i* main_menu = new Vector2i(120, 180);
	int Width = 1600;
	int Height = 900;
	Color Sections = Color(255, 255, 255, 70);
	Color GridColor = Color(255, 255, 255, 128);
	Color Player_theme = Color(0, 255, 255, 200);
	Color Computer_theme = Color(255, 0, 0, 200);
	Color TextColor = Color(255, 255, 255, 200);
	Color HitColor = Color(235, 33, 46, 150);
	Color ShipColor = Color(0, 195, 227, 150);
	PlayState mode;
	void clean()
	{
		delete player1, player2, main_menu;
	}

}UI;

#endif