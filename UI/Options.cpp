#include "Options.h"

Options::Options(int width, int height, RenderWindow& window)
{
	//Pointer to window
	Menu = &window;
	Menu->clear();

	//Set Background
	OBackground_img.loadFromFile(".\\Images\\Menu_Options.jpg");
	OBackground.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	OBackground.setTexture(&OBackground_img);
	Menu->draw(OBackground);

	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}

	mode = sound;
	Menu->display();
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

	}
}