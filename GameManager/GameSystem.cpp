#include "GameSystem.h"

GameSystem::GameSystem(int width, int height, RenderWindow& window)
{
	//Pointer to window
	Menu = &window;
	Menu->clear();

	//Set Background
	PBackground_img.loadFromFile(".\\Images\\Load.jpg");
	PBackground.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	PBackground.setTexture(&PBackground_img);
	Menu->draw(PBackground);

	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}
	
	//Display Player's Grid
	grid[0].draw(*Menu, player);

	//Display Computer's Grid
	grid[1].draw(*Menu, computer);

	//Display Text
	Players_name[0].setFont(font);
	Players_name[0].setString("Player");
	Players_name[0].setCharacterSize(50);
	Players_name[0].setFillColor(sf::Color(0, 255, 255, 150));
	Players_name[0].setPosition(100, 170);
	Menu->draw(Players_name[0]);
	Players_name[1].setFont(font);
	Players_name[1].setString("Computer");
	Players_name[1].setCharacterSize(50);
	Players_name[1].setFillColor(sf::Color(255, 0, 0, 150));
	Players_name[1].setPosition(600, 170);
	Menu->draw(Players_name[1]);

	setMode(prep);
	Menu->display();
	while (CurrentMode() != closed)
	{
		sf::Event event;
		while (Menu->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Menu->close();
			if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				// The escape key was pressed
				setMode(closed);
			}
		}

	}
}
