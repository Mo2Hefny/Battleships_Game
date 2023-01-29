#include "Main_Menu.h"

MainMenu::MainMenu(RenderWindow& window)
{
	//Pointer to window
	Menu = &window;

	//Set Backgrounds
	Background_img.loadFromFile(".\\Images\\Menu_Background.jpg");

	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}
	
	for (int i = 0; i < Max_Menu_Options; i++)
	{
		MenuText[i].setFont(font);
		MenuText[i].setFillColor(Color::White);
		MenuText[i].setCharacterSize(70);
		MenuText[i].setPosition(UI.main_menu->x, UI.main_menu->y + i * 100);
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
	{
		Menu->draw(MenuText[i]);
		item_pos[i] = (Vector2i)MenuText[i].getPosition();
		width[i] = MenuText[i].getLocalBounds().width;
		height[i] = MenuText[i].getLocalBounds().height;
	}
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

/*
* Switch - switch to the choosen Menu option.
*/
void MainMenu::Switch()
{
	if (CurrentSelected() == -1) return;

	switch (CurrentSelected())
	{
	case 0:
		Menu->clear();
		Menu->display();
		Game = new GameSystem(_WIDTH_, _HEIGHT_, *Menu);
		Game->Execute();
		delete Game;
		Game = NULL;
		break;
	case 1:
		options = new Options(_WIDTH_, _HEIGHT_, *Menu);
		delete options;
		options = NULL;
		break;
	case 2:
		Menu->close();
		break;
	default:
		break;
	}
}

/*
* OnText - checks if the mouse is on the text and updates the selected item.
*/
int MainMenu::OnText() const
{
	Vector2i pos = Mouse::getPosition(*Menu);

	/*cout << "x: " << pos.x << " y: " << pos.y << endl;
	cout << "x1: " << item_pos[0].x << " y1: " << item_pos[0].y << endl;
	cout << ": " << pos.x - item_pos[0].x << " : " << width[0] << endl;*/

	if (pos.x - item_pos[0].x < width[0] && pos.x - item_pos[0].x > 0 && pos.y - item_pos[0].y < height[0] && pos.y - item_pos[0].y > 0)
	{
		return 0;
	}
	else if (pos.x - item_pos[1].x < width[1] && pos.x - item_pos[1].x > 0 && pos.y - item_pos[1].y < height[1] && pos.y - item_pos[1].y > 0)
	{

		return 1;
	}
	else if (pos.x - item_pos[2].x < width[2] && pos.x - item_pos[2].x > 0 && pos.y - item_pos[2].y < height[2] && pos.y - item_pos[2].y > 0)
	{
		return 2;
	}
	return -1;
}

void MainMenu::Execute()
{
	RectangleShape Background;
	Background.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	Background.setTexture(&Background_img);

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
					Switch();
				}
			}
			
			//Mouse Input
			if (!Mouse::isButtonPressed(Mouse::Left))
			{
				int x = OnText();
				if (x == 0 && MainMenuSelected != 0)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 0;
					MenuText[MainMenuSelected].setFillColor(Color::Cyan);
				}
				else if (x == 1 && MainMenuSelected != 1)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 1;
					MenuText[MainMenuSelected].setFillColor(Color::Cyan);
				}
				else if (x == 2 && MainMenuSelected != 2)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 2;
					MenuText[MainMenuSelected].setFillColor(Color::Cyan);
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (OnText() != -1)
					Switch();
			}
		}

		Menu->clear();
		Menu->draw(Background);
		draw();
		Menu->display();
	}
}