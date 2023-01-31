#include "Main_Menu.h"

MainMenu::MainMenu(RenderWindow& window)
{
	srand(time(0));
	// Pointer to window
	Menu = &window;

	// Set Backgrounds
	switch (abs(rand()) % 3)
	{
	case 0:
		Background_img.loadFromFile(".\\Images\\Menu.jpg");
		break;
	case 1:
		Background_img.loadFromFile(".\\Images\\Menu1.jpg");
		break;
	case 2:
		Background_img.loadFromFile(".\\Images\\Menu_Background.jpg");
		break;
	}

	// Set Game Font
	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}
	
	// Set Menu Items
	// Play
	MenuText[0].setString("Play");
	// Options
	MenuText[1].setString("Options");
	// Exit
	MenuText[2].setString("Exit");
	for (int i = 0; i < Max_Menu_Options; i++)
	{
		MenuText[i].setFont(font);
		MenuText[i].setFillColor(Color::White);
		MenuText[i].setCharacterSize(70);
		MenuText[i].setPosition(UI.main_menu->x, UI.main_menu->y + i * 100);

		// Updates Text Borders
		item_pos[i] = (Vector2i)MenuText[i].getPosition();
		width[i] = MenuText[i].getLocalBounds().width;
		height[i] = MenuText[i].getLocalBounds().height;
	}
	
	MainMenuSelected = -1;

	// Initialize pointers
	Game = NULL;
	options = NULL;
	
}

MainMenu::~MainMenu()
{
	if (Game != NULL)
		delete Game;
	if (options != NULL)
		delete options;
}

/*
* draw - draws the menu items.
*/
void MainMenu::draw()
{
	for (int i = 0; i < Max_Menu_Options; i++)
	{
		Menu->draw(MenuText[i]);
	}
}

/*
* MoveUp - Changes the selected menu item.
*/
void MainMenu::MoveUp()
{	
	if (MainMenuSelected >= 0)
	{
		MenuText[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		MainMenuSelected = (MainMenuSelected == -1) ? 2 : MainMenuSelected;
		MenuText[MainMenuSelected].setFillColor(UI.Player_theme);
	}
}

/*
* MoveDown - Changes the selected menu item.
*/
void MainMenu::MoveDown()
{
	if (MainMenuSelected < Max_Menu_Options)
	{
		MenuText[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		MainMenuSelected = (MainMenuSelected == 3) ? 0 : MainMenuSelected;
		MenuText[MainMenuSelected].setFillColor(UI.Player_theme);
	}
}

/*
* Switch - switch to the choosen Menu option.
*/
void MainMenu::Switch()
{
	if (CurrentSelected() == -1) return;
	if (options == NULL)
		options = new Options(*Menu);
	switch (CurrentSelected())
	{
	case 0:		// Start Game
		Load();		// Loading Screen
		if (Game == NULL)
			Game = new GameSystem(*Menu, options);
		Game->Execute();
		delete Game;
		Game = NULL;
		break;
	case 1:		// Open Settings
		options->Execute();
		break;
	case 2:		// Close Game
		Menu->close();
		break;
	default:
		break;
	}
}

/*
* Load - Switch to a load screen till the game loads.
*/
void MainMenu::Load()
{
	Menu->clear();
	RectangleShape Background;
	Texture LBackground_img;
	Background.setSize(Vector2f(_WIDTH_, _HEIGHT_));

	// Set Loading Screen Background
	switch (abs(rand()) % 3)
	{
	case 0:
		LBackground_img.loadFromFile(".\\Images\\Load.jpg");
		break;
	case 1:
		LBackground_img.loadFromFile(".\\Images\\Load1.jpg");
		break;
	case 2:
		LBackground_img.loadFromFile(".\\Images\\Load2.jpg");
		break;
	}
	Background.setTexture(&LBackground_img);
	Menu->draw(Background);

	// Loading Text
	Text loading;
	loading.setFont(font);
	loading.setFillColor(UI.TextColor);
	loading.setString("Loading...");
	loading.setCharacterSize(30);
	loading.setPosition(67, 815);
	Menu->draw(loading);
	Menu->display();
}

/*
* OnText - checks if the mouse is on the text and updates the selected item.
*/
int MainMenu::OnText() const
{
	Vector2i pos = Mouse::getPosition(*Menu);

	// Terminal Updates
	printf("Clicked at position: (%d, %d)\n", pos.x, pos.y);

	// Clicked Play
	if (pos.x - item_pos[0].x < width[0] && pos.x - item_pos[0].x > 0 && pos.y - item_pos[0].y < height[0] && pos.y - item_pos[0].y > 0)
	{
		return 0;
	}
	// Clicked Options
	else if (pos.x - item_pos[1].x < width[1] && pos.x - item_pos[1].x > 0 && pos.y - item_pos[1].y < height[1] && pos.y - item_pos[1].y > 0)
	{

		return 1;
	}
	// Clicked Exit
	else if (pos.x - item_pos[2].x < width[2] && pos.x - item_pos[2].x > 0 && pos.y - item_pos[2].y < height[2] && pos.y - item_pos[2].y > 0)
	{
		return 2;
	}
	// Clicked on Screen
	return -1;
}

/*
* Execute - Runs the main menu.
*/
void MainMenu::Execute()
{
	RectangleShape Background;
	Background.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	Background.setTexture(&Background_img);

	UI_s.Main_music.play();

	while (Menu->isOpen())
	{
		Event event;
		while (Menu->pollEvent(event))
		{
			// Request for closing the window
			if (event.type == Event::Closed)
				Menu->close();

			// KeyBoard Input
			if (event.type == Event::KeyPressed)
			{
			    // The escape key was pressed
				if (event.key.code == sf::Keyboard::Escape)
					Menu->close();

				// The Up key was pressed
				else if (event.key.code == sf::Keyboard::Up)
				{
					MoveUp();
					UI_s.hover.play();		//Play hovering sound
					break;
				}
				// The Down key was pressed
				if (event.key.code == sf::Keyboard::Down)
				{
					MoveDown();
					UI_s.hover.play();		//Play hovering sound
					break;
				}
				// The Enter key was pressed
				if (event.key.code == sf::Keyboard::Enter)
				{
					UI_s.select.play();		//Play select sound
					Switch();
				}
			}
			
			//Mouse Input
			if (!Mouse::isButtonPressed(Mouse::Left))
			{
				int x = OnText();
				// Hovering on Play
				if (x == 0 && MainMenuSelected != 0)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 0;
					MenuText[MainMenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();		//Play hovering sound
				}
				// Hovering on Options
				else if (x == 1 && MainMenuSelected != 1)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 1;
					MenuText[MainMenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();		//Play hovering sound
				}
				// Hovering on Exit
				else if (x == 2 && MainMenuSelected != 2)
				{
					MenuText[MainMenuSelected].setFillColor(Color::White);
					MainMenuSelected = 2;
					MenuText[MainMenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();		//Play hovering sound
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (OnText() != -1)
				{
					UI_s.select.play();		//Play select sound
					Switch();
				}
			}
		}

		// Updates Window
		Menu->clear();
		Menu->draw(Background);
		draw();
		Menu->display();
	}
}