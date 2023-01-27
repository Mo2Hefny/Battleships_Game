#ifndef OPTIONS
#define OPTIONS

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"
using namespace std;
using namespace sf;

class Options
{
	OptionMenu mode;
	Font font;
	RenderWindow* Menu;
	Texture OBackground_img;
	RectangleShape OBackground;
public:
	Options(int width, int height, RenderWindow& window);
	void Execute();
	void draw();
	OptionMenu CurrentMode() const { return mode; }

	//setters
	void setMode(OptionMenu state) { mode = state; }

};

#endif