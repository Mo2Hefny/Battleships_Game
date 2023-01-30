#include "Options.h"

Options::Options(RenderWindow& window)
{
	//Pointer to window
	Menu = &window;
	Menu->clear();

	//Set Background
	OBackground_img.loadFromFile(".\\Images\\Options.jpeg");
	OBackground.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	OBackground.setTexture(&OBackground_img);

	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}

	mode = sound;
	
	
}

void Options::draw()
{
	while (CurrentMode() != closed_op)
	{
		sf::Event event;
		while (Menu->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Menu->close();
			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				// The escape key was pressed
				setMode(closed_op);
			}
		}
		Menu->clear();
		Menu->draw(OBackground);
		Menu->display();
	}
}

void Options::Execute()
{
	Menu->clear();
	Menu->display();
	setMode(sound);
	draw();
}