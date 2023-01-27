#include "Main_Menu.h"

MainMenu::MainMenu(int width, int height, RenderWindow& window)
{
	//Pointer to window
	Menu = &window;

	//Set Backgrounds
	Background_img.loadFromFile(".\\Images\\Menu_Background.jpg");
	PBackground_img.loadFromFile(".\\Images\\Load.jpg");
	OBackground_img.loadFromFile(".\\Images\\Menu_Options.jpg");

	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}
	
	for (int i = 0; i < Max_Menu_Options; i++)
	{
		MenuText[i].setFont(font);
		MenuText[i].setFillColor(Color::White);
		MenuText[i].setCharacterSize(70);
		MenuText[i].setPosition(120, 150 + i * 100);
	}
	//Play
	MenuText[0].setString("Play");
	//Options
	MenuText[1].setString("Options");
	//Exit
	MenuText[2].setString("Exit");

	MainMenuSelected = -1;
}

void MainMenu::draw()
{
	for (int i = 0; i < Max_Menu_Options; i++)
		Menu->draw(MenuText[i]);
}

void MainMenu::MoveUp()
{	
	if (MainMenuSelected >= 0)
	{
		MenuText[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		MainMenuSelected = (MainMenuSelected == -1) ? 2 : MainMenuSelected;
		MenuText[MainMenuSelected].setFillColor(Color::Cyan);
	}
}

void MainMenu::MoveDown()
{
	if (MainMenuSelected < Max_Menu_Options)
	{
		MenuText[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		MainMenuSelected = (MainMenuSelected == 3) ? 0 : MainMenuSelected;
		MenuText[MainMenuSelected].setFillColor(Color::Cyan);
	}
}

void MainMenu::Execute()
{
	RectangleShape Background, PBackground, OBackground;
	Background.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	Background.setTexture(&Background_img);
	PBackground.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	PBackground.setTexture(&PBackground_img);
	OBackground.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	OBackground.setTexture(&OBackground_img);

	while (Menu->isOpen())
	{
		Event event;
		while (Menu->pollEvent(event))
		{
			// Request for closing the window
			if (event.type == Event::Closed)
				Menu->close();
			if (event.type == Event::KeyPressed)
			{
			    // The escape key was pressed
				if (event.key.code == sf::Keyboard::Escape)
					Menu->close();
				else if (event.key.code == sf::Keyboard::Up)
				{
					MoveUp();
					break;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					MoveDown();
					break;
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (CurrentSelected() == -1) break;
					RenderWindow Play(VideoMode(_WIDTH_, _HEIGHT_), "Battleships!!");
					RenderWindow Options(VideoMode(_WIDTH_, _HEIGHT_), "Options");

					switch (CurrentSelected())
					{
					case 0:
						while (Play.isOpen())
						{
							Event event;
							while (Play.pollEvent(event))
							{
								// Request for closing the window
								if (event.type == Event::Closed)
									Play.close();
								if (event.type == Event::KeyPressed)
								{
									// The escape key was pressed
									if (event.key.code == sf::Keyboard::Escape)
										Play.close();
								}
							}
							Options.close();
							Play.clear();
							Play.draw(PBackground);
							Play.display();
						}
						break;
					case 1:
						while (Options.isOpen())
						{
							Event event;
							while (Options.pollEvent(event))
							{
								// Request for closing the window
								if (event.type == Event::Closed)
									Options.close();
								if (event.type == Event::KeyPressed)
								{
									// The escape key was pressed
									if (event.key.code == sf::Keyboard::Escape)
										Options.close();
								}
							}
							Play.close();
							Options.clear();
							Options.draw(OBackground);
							Options.display();
						}
						break;
					case 2:
						Menu->close();
						break;
					default:
						break;
					}
				}
			}
			
			//Mouse Input
			Vector2i pos = Mouse::getPosition();
			if (!Mouse::isButtonPressed(Mouse::Left))
			{
				if (pos.x > 452 && pos.x < 600 && pos.y > 379 && pos.y < 433 && MainMenuSelected != 0)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 0;
					MenuText[MainMenuSelected].setFillColor(Color::Cyan);
				}
				else if (pos.x > 452 && pos.x < 722 && pos.y > 474 && pos.y < 536 && MainMenuSelected != 1)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 1;
					MenuText[MainMenuSelected].setFillColor(Color::Cyan);
				}
				else if (pos.x > 452 && pos.x < 590 && pos.y > 580 && pos.y < 630 && MainMenuSelected != 2)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 2;
					MenuText[MainMenuSelected].setFillColor(Color::Cyan);
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (CurrentSelected() == -1) break;
				RenderWindow Play(VideoMode(_WIDTH_, _HEIGHT_), "Battleships!!");
				RenderWindow Options(VideoMode(_WIDTH_, _HEIGHT_), "Options");

				switch (CurrentSelected())
				{
				case 0:
					while (Play.isOpen())
					{
						Event event;
						while (Play.pollEvent(event))
						{
							// Request for closing the window
							if (event.type == Event::Closed)
								Play.close();
							if (event.type == Event::KeyPressed)
							{
								// The escape key was pressed
								if (event.key.code == sf::Keyboard::Escape)
									Play.close();
							}
						}
						Options.close();
						Play.clear();
						Play.draw(PBackground);
						Play.display();
					}
					break;
				case 1:
					while (Options.isOpen())
					{
						Event event;
						while (Options.pollEvent(event))
						{
							// Request for closing the window
							if (event.type == Event::Closed)
								Options.close();
							if (event.type == Event::KeyPressed)
							{
								// The escape key was pressed
								if (event.key.code == sf::Keyboard::Escape)
									Options.close();
							}
						}
						Play.close();
						Options.clear();
						Options.draw(OBackground);
						Options.display();
					}
					break;
				case 2:
					Menu->close();
					break;
				default:
					break;
				}
			}
		}
		Menu->clear();
		Menu->draw(Background);
		draw();
		Menu->display();
	}
}