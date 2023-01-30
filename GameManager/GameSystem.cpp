#include "GameSystem.h"
#include "../Ships/Carrier.h"
#include "../Ships/Battleship.h"
#include "../Ships/Cruiser.h"
#include "../Ships/Submarine.h"
#include "../Ships/Warship.h"

GameSystem::GameSystem(RenderWindow& window, Options* o)
{
	//Pointer to window
	game_window = &window;
	settings = o;

	//Set Background
	
	switch (abs(rand()) % 2)
	{
	case 0:
		PBackground_img.loadFromFile(".\\Images\\game.jpg");
		break;
	case 1:
		PBackground_img.loadFromFile(".\\Images\\game1.jpg");
		break;
	}
	PBackground.setSize(Vector2f(_WIDTH_, _HEIGHT_));
	PBackground.setTexture(&PBackground_img);
	if (!font.loadFromFile(".\\Font\\Alexandria.ttf"))
	{
		cout << "No font is selected.\n";
	}
	
	//Display Player's Grid
	grid[0].setWindow(*game_window);

	//Display Computer's Grid
	grid[1].setWindow(*game_window);

	player = new Player(*game_window, &grid[0]);
	computer = new Computer(*game_window, &grid[1]);

}

GameSystem::~GameSystem()
{
	if (player != NULL)
		delete player;
	if (computer != NULL)
		delete computer;
}

//======================================================================================//
//								     UI Setup		   								    //
//======================================================================================//

/*
* PrepUI - Display the UI for the prep phase.
*/
void GameSystem::PrepUI()
{
	//Display Sections
	//Grid Section
	Sections[0].setPosition(45, 105);
	Sections[0].setSize(Vector2f(845, 475));
	Sections[0].setFillColor(UI.Sections);

	//Ships Section
	Sections[1].setPosition(960, 105);
	Sections[1].setSize(Vector2f(585, 670));
	Sections[1].setFillColor(UI.Sections);

	//Status Bar Section
	Sections[2].setPosition(45, 803);
	Sections[2].setSize(Vector2f(1500, 80));
	Sections[2].setFillColor(UI.Sections);

	//Display Underlines
	//Player's
	Underline[0].setPosition(UI.player1->x + 5, UI.player1->y - 15);
	Underline[0].setSize(Vector2f(285, 4));
	Underline[0].setFillColor(Color(123, 255, 255, 100));

	//Computer's
	Underline[1].setPosition(UI.player2->x + 5, UI.player1->y - 15);
	Underline[1].setSize(Vector2f(285, 4));
	Underline[1].setFillColor(Color(235, 33, 46, 100));

	//Ships'
	Underline[2].setPosition(995, UI.player1->y - 15);
	Underline[2].setSize(Vector2f(515, 4));
	Underline[2].setFillColor(Color(225, 225, 225, 100));

	//Display Text
	//Display Ship text
	prep_ships.setFont(font);
	prep_ships.setCharacterSize(50);
	prep_ships.setFillColor(UI.TextColor);
	prep_ships.setPosition(960 + (585 - prep_ships.getLocalBounds().width) / 2, UI.player1->y - 80);

	//Display Names
	Players_name[0].setFont(font);
	Players_name[0].setString("Player");
	Players_name[0].setCharacterSize(50);
	Players_name[0].setFillColor(UI.Player_theme);
	Players_name[0].setPosition(UI.player1->x + (295 - Players_name[0].getLocalBounds().width) / 2, UI.player1->y - 80);

	Players_name[1].setFont(font);
	Players_name[1].setString("Computer");
	Players_name[1].setCharacterSize(50);
	Players_name[1].setFillColor(UI.Computer_theme);
	Players_name[1].setPosition(UI.player2->x + (295 - Players_name[1].getLocalBounds().width) / 2, UI.player1->y - 80);

	//Display Status Bar
	status_barT.loadFromFile(".\\Images\\info.png");
	status_bar.setTexture(status_barT);
	status_bar.setPosition(67, 815);
	status_bar.setColor(Color(255, 255, 255, 170));
	status_bar.setScale(0.1, 0.1);
	status_bar_msg.setFont(font);
	status_bar_msg.setCharacterSize(35);
	status_bar_msg.setFillColor(UI.TextColor);
	status_bar_msg.setPosition(140, 820);

	//Display Ships
	//Carrier
	carrierT.loadFromFile(".\\Images\\Carrier.png");
	carrier.setTexture(carrierT);
	carrier.setPosition(1000, UI.player1->y - 50);
	carrier.setScale(0.5, 0.5);

	//battleship
	battleshipT.loadFromFile(".\\Images\\Battleship.png");
	battleship.setTexture(battleshipT);
	battleship.setPosition(1000, UI.player1->y - 24);
	battleship.setScale(0.55, 0.5);

	//cruiser
	cruiserT.loadFromFile(".\\Images\\Cruiser.png");
	cruiser.setTexture(cruiserT);
	cruiser.setPosition(1000, UI.player1->y + 170);
	cruiser.setScale(0.16, 0.16);

	//Submarine
	subT.loadFromFile(".\\Images\\Submarine.png");
	sub.setTexture(subT);
	sub.setPosition(1000, UI.player1->y + 215);
	sub.setScale(0.07, 0.07);

	//warship
	warshipT.loadFromFile(".\\Images\\Warship.png");
	warship.setTexture(warshipT);
	warship.setPosition(1000, UI.player1->y + 390);
	warship.setScale(0.14, 0.14);

	//Display Menu UI
	//Icon
	menu_dropT.loadFromFile(".\\Images\\list.png");
	menu_drop.setTexture(menu_dropT);
	menu_drop.setScale(0.1, 0.1);
	menu_drop.setPosition(_WIDTH_ - 115, 35);
	menu_drop.setColor(Color(255, 255, 255, 170));

	
}

void GameSystem::PrepMenu()
{
	//Menu
	popup.setPosition(_WIDTH_ / 2 - 200, _HEIGHT_ / 2 - 300);
	popup.setSize(Vector2f(400, 600));
	popup.setFillColor(UI.PopUps);

	//Exit Button
	menuOp[0].setPosition(_WIDTH_ / 2 - 105, _HEIGHT_ / 2 - 300 + 70);
	menuOp[0].setSize(Vector2f(210, 70));
	menuOp[0].setFillColor(UI.Sections);
	menuOp[1].setPosition(_WIDTH_ / 2 - 105, _HEIGHT_ / 2 - 300 + 200);
	menuOp[1].setSize(Vector2f(210, 70));
	menuOp[1].setFillColor(UI.Sections);
	menuOp[2].setPosition(_WIDTH_ / 2 - 105, _HEIGHT_ / 2 - 300 + 330);
	menuOp[2].setSize(Vector2f(210, 70));
	menuOp[2].setFillColor(UI.Sections);
	menuOp[3].setPosition(_WIDTH_ / 2 - 60, _HEIGHT_ / 2 + 190);
	menuOp[3].setSize(Vector2f(120, 60));
	menuOp[3].setFillColor(UI.Sections);

	menuOpT[0].setFont(font);
	menuOpT[0].setString("Settings");
	menuOpT[0].setCharacterSize(30);
	menuOpT[0].setFillColor(UI.TextColor);
	menuOpT[0].setPosition((_WIDTH_ - menuOpT[0].getLocalBounds().width) / 2, _HEIGHT_ / 2 - 300 + 90);
	menuOpT[1].setFont(font);
	menuOpT[1].setString("Toggle SFX");
	menuOpT[1].setCharacterSize(30);
	menuOpT[1].setFillColor(UI.TextColor);
	menuOpT[1].setPosition((_WIDTH_ - menuOpT[1].getLocalBounds().width) / 2, _HEIGHT_ / 2 - 300 + 220);
	menuOpT[2].setFont(font);
	menuOpT[2].setString("Toggle Music");
	menuOpT[2].setCharacterSize(30);
	menuOpT[2].setFillColor(UI.TextColor);
	menuOpT[2].setPosition((_WIDTH_ - menuOpT[2].getLocalBounds().width) / 2, _HEIGHT_ / 2 - 300 + 350);
	menuOpT[3].setFont(font);
	menuOpT[3].setString("Exit");
	menuOpT[3].setCharacterSize(30);
	menuOpT[3].setFillColor(UI.TextColor);
	menuOpT[3].setPosition((_WIDTH_ - menuOpT[3].getLocalBounds().width) / 2, _HEIGHT_ / 2 + 205);

	MenuSelected = -1;
}

void GameSystem::OpenMenu()
{
	PrepMenu();
	UI_s.open_menu.play();
	while (CurrentMode() == menu)
	{
		sf::Event event;
		while (game_window->pollEvent(event))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (OpenedMenu())
				{
					UI_s.open_menu.play();
					setMode(UI.mode);
				}
			}
			if (event.type == Event::KeyPressed)
			{
				// The escape key was pressed
				if (event.key.code == sf::Keyboard::Escape)
				{
					UI_s.open_menu.play();
					setMode(UI.mode);
				}
				if (event.key.code == sf::Keyboard::I)
				{
					UI_s.open_menu.play();
					setMode(UI.mode);
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					MoveUp();
					UI_s.hover.play();
					break;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					MoveDown();
					UI_s.hover.play();
					break;
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					UI_s.select.play();
					Switch();
				}
			}

			//Mouse Input
			if (!Mouse::isButtonPressed(Mouse::Left))
			{
				int x = OnText();
				if (x == 0 && MenuSelected != 0)
				{
					menuOpT[MenuSelected].setFillColor(UI.TextColor);
					MenuSelected = 0;
					menuOpT[MenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();
				}
				else if (x == 1 && MenuSelected != 1)
				{
					menuOpT[MenuSelected].setFillColor(UI.TextColor);
					MenuSelected = 1;
					menuOpT[MenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();
				}
				else if (x == 2 && MenuSelected != 2)
				{
					menuOpT[MenuSelected].setFillColor(UI.TextColor);
					MenuSelected = 2;
					menuOpT[MenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();
				}
				else if (x == 3 && MenuSelected != 3)
				{
					menuOpT[MenuSelected].setFillColor(UI.TextColor);
					MenuSelected = 3;
					menuOpT[MenuSelected].setFillColor(UI.Player_theme);
					UI_s.hover.play();
				}
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (OnText() != -1)
				{
					UI_s.select.play();
					Switch();
				}
			}
		}
		game_window->clear();
		draw();
		game_window->draw(popup);
		game_window->draw(menuOp[0]);
		game_window->draw(menuOp[1]);
		game_window->draw(menuOp[2]);
		game_window->draw(menuOp[3]);
		game_window->draw(menuOpT[0]);
		game_window->draw(menuOpT[1]);
		game_window->draw(menuOpT[2]);
		game_window->draw(menuOpT[3]);
		game_window->display();
	}
}

void GameSystem::Switch()
{
	if (CurrentSelected() == -1) return;
	switch (CurrentSelected())
	{
	case 0:
		settings->Execute();
		break;
	case 1:
		if (VOLUME)
			UI_s.setSFXVolume(0);
		else
			UI_s.setSFXVolume(UI_s.oldVolume);
		break;
	case 2:
		if (MUSIC_VOLUME)
			UI_s.setMusicVolume(0);
		else
			UI_s.setMusicVolume(UI_s.oldMusic);
		break;
	case 3:
		UI_s.select.stop();
		UI_s.open_menu.play();
		setMode(UI.mode);
		break;
	default:
		break;
	}
}

void GameSystem::MoveUp()
{
	if (MenuSelected >= 0)
	{
		menuOpT[MenuSelected].setFillColor(Color::White);
		MenuSelected--;
		MenuSelected = (MenuSelected == -1) ? 2 : MenuSelected;
		menuOpT[MenuSelected].setFillColor(UI.Player_theme);
	}
}

void GameSystem::MoveDown()
{
	if (MenuSelected < 4)
	{
		menuOpT[MenuSelected].setFillColor(Color::White);
		MenuSelected++;
		MenuSelected = (MenuSelected == 3) ? 0 : MenuSelected;
		menuOpT[MenuSelected].setFillColor(UI.Player_theme);
	}
}

/*
* OnText - checks if the mouse is on the text and updates the selected item.
*/
int GameSystem::OnText() const
{
	Vector2i pos = Mouse::getPosition(*game_window);

	if (pos.x > _WIDTH_ / 2 - 105 && pos.x < _WIDTH_ / 2 + 105)
	{
		if (pos.y > _HEIGHT_ / 2 - 300 + 70 && pos.y < _HEIGHT_ / 2 - 300 + 140)
		{
			return 0;
		}
		else if (pos.y > _HEIGHT_ / 2 - 300 + 200 && pos.y < _HEIGHT_ / 2 - 300 + 270)
		{

			return 1;
		}
		else if (pos.y > _HEIGHT_ / 2 - 300 + 330 && pos.y < _HEIGHT_ / 2 - 300 + 400)
		{
			return 2;
		}

	}
	if (pos.x > _WIDTH_ / 2 - 60 && pos.x < _WIDTH_ / 2 + 60 && pos.y > _HEIGHT_ / 2 + 190 && pos.y < _HEIGHT_ / 2 + 300)
	{
		return 3;
	}
	return -1;
}

void GameSystem::draw()
{
	game_window->draw(PBackground);
	game_window->draw(Sections[0]);
	game_window->draw(Sections[1]);
	game_window->draw(Sections[2]);
	game_window->draw(Underline[0]);
	game_window->draw(Underline[1]);
	game_window->draw(Underline[2]);
	game_window->draw(carrier);
	game_window->draw(battleship);
	game_window->draw(cruiser);
	game_window->draw(sub);
	game_window->draw(warship);
	game_window->draw(Players_name[0]);
	game_window->draw(Players_name[1]);
	game_window->draw(status_bar);
	game_window->draw(status_bar_msg);
	game_window->draw(prep_ships);
	game_window->draw(menu_drop);
	grid[0].draw(0);
	grid[1].draw(1);
}

//======================================================================================//
//								Preparation Phase										//
//======================================================================================//

/*
* PrepPhase - Preparation phase for the gameplay.
*/
void GameSystem::PrepPhase()
{
	setMode(prep);
	UI.mode = prep;

	prep_ships.setString("Deploy Your Ships");
	setString("Deploy Your Ships!!");
	PrepUI();

	PrepComputer();

	grid[0].resetPlacements();
	while (UI.mode == prep)
	{
		sf::Event event;
		while (game_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				UI.mode = closed;
				game_window->close();
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Ship* temp = player->getSelected();
				if (OpenedMenu())
					setMode(menu);
				SelectedShip();
				if (player->getSelected() != NULL && temp != player->getSelected())
				{
					if (temp != NULL)
						UpdateGrid(UI.ShipColor, temp->getHitbox());

					UI_s.select.play();
					grid[0].setPlacements(player->getSelected()->getHitbox(), 0);
					UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
					player->getSelected()->PrepPhase();
					grid[0].setPlacements(player->getSelected()->getHitbox(), 1);
					UpdateGrid(UI.ShipColorSelected, player->getSelected()->getHitbox());
				}
			}
			if (event.type == Event::KeyPressed)
			{
				// The escape key was pressed
				if (event.key.code == sf::Keyboard::Escape)
				{
					UI.mode = closed;
					setMode(closed);
				}
				if (player->getSelected() != NULL)
				{
					if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
					{
						grid[0].setPlacements(player->getSelected()->getHitbox(), 0);
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveUp();
						grid[0].setPlacements(player->getSelected()->getHitbox(), 1);
						UpdateGrid(UI.ShipColorSelected, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
					{
						grid[0].setPlacements(player->getSelected()->getHitbox(), 0);
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveDown();
						grid[0].setPlacements(player->getSelected()->getHitbox(), 1);
						UpdateGrid(UI.ShipColorSelected, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
					{
						grid[0].setPlacements(player->getSelected()->getHitbox(), 0);
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveLeft();
						grid[0].setPlacements(player->getSelected()->getHitbox(), 1);
						UpdateGrid(UI.ShipColorSelected, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
					{
						grid[0].setPlacements(player->getSelected()->getHitbox(), 0);
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveRight();
						grid[0].setPlacements(player->getSelected()->getHitbox(), 1);
						UpdateGrid(UI.ShipColorSelected, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::R)
					{
						grid[0].setPlacements(player->getSelected()->getHitbox(), 0);
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->Rotate();
						grid[0].setPlacements(player->getSelected()->getHitbox(), 1);
						UpdateGrid(UI.ShipColorSelected, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Enter)
					{
						int x = grid[0].CheckValidity();
						if (x == 1)
						{
							UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
							setString("Your Placements Are Valid. Starting Game...");
							setMode(game);
							UI.mode = game;
							UI_s.select.play();
						}
						else if (x == 0)
						{
							setString("Your Ships Are Overlapping.");
						}
						else if (x == -1)
						{
							setString("Deploy All Of Your Ships To Proceed.");
						}
					}
				}
				if (event.key.code == sf::Keyboard::I)
				{
					setMode(menu);
				}
				
			}
			
		}
		if (CurrentMode() == menu)
			OpenMenu();
		game_window->clear();
		draw();
		game_window->display();
		
	}
	if (mode == game)
		GamePhase();
}

void GameSystem::PrepComputer()
{
	bool prepping;
	do
	{
		grid[1].resetPlacements();
		prepping = false;
		computer->PrepPhase();
		for (int i = 0; i < 5; i++)
		{
			grid[1].setPlacements(computer->getShip(i)->getHitbox(), 1);
		}
	} while (!grid[1].CheckValidity());


	/*for (int i = 0; i < 5; i++)
	{
		UpdateGrid(UI.HitColor, computer->getShip(i)->getHitbox(), 1);
	}*/
}

void GameSystem::UpdateGrid(Color& c, vector<Vector2i>& hitbox, int team)
{
	grid[team].ColorShip(c, hitbox);
}

//======================================================================================//
//								  Gameplay Phase		   								//
//======================================================================================//

void GameSystem::GamePhase()
{
	/*for (int i = 0; i < 5; i++)
	{
		UpdateGrid(UI.GridColor, computer->getShip(i)->getHitbox(), 1);
	}*/

	carrier.setColor(Color::White);
	battleship.setColor(Color::White);
	cruiser.setColor(Color::White);
	sub.setColor(Color::White);
	warship.setColor(Color::White);
	prep_ships.setString("Your Ships");
	PrepUI();

	player->setPlacements();
	computer->setPlacements();
	computer->setEnemyInfo(player);

	bool turn = true;
	while (UI.mode == game && CheckWinner() == 0)
	{
		Vector2i pos_comp;
		if (!turn)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(700));
			GameComputer(pos_comp);
			turn = !turn;
		}
		if (turn)
			setString("Choose a Position To Strike Commander.");
		sf::Event event;
		while (game_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				UI.mode = closed;
				game_window->close();
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (OpenedMenu())
					setMode(menu);
				Vector2i pos = getGridPos();
				if (pos.x != -1 && pos.y != -1 && turn)
				{
					cout << "x: " << pos.x << " y: " << pos.y << endl;
					if (!computer->ShotTracker(pos))
						continue;
					if (grid[1].HitGrid(pos))
					{
						setString("Target Hit!");
					}
					else
					{
						setString("We Missed Our Target Comander.");
					}
					for (int i = 0; i < 5; i++)
					{
						if (computer->getShip(i)->getHealth() == dead)
						{
							UpdateGrid(UI.HitColor, computer->getShip(i)->getHitbox(), 1);
						}
					}
					if (CheckWinner() == -1)	//Player Won
						break;
					turn = !turn;
				}
				while (Mouse::isButtonPressed(Mouse::Left))
				{

				}
			}
			if (event.type == Event::KeyPressed)
			{
				// The escape key was pressed
				if (event.key.code == sf::Keyboard::Escape)
				{
					UI.mode = closed;
					setMode(closed);
				}
				if (event.key.code == sf::Keyboard::I)
				{
					setMode(menu);
				}
			}
		}
		if (CurrentMode() == menu)
			OpenMenu();
		game_window->clear();
		draw();
		game_window->display();
	}
	if (CurrentMode() != closed)
	{
		while (!Mouse::isButtonPressed(Mouse::Left))
		{

		}
		while (Mouse::isButtonPressed(Mouse::Left))
		{

		}
	}
}

void GameSystem::GameComputer(Vector2i& pos)
{
	computer->PickTarget(pos);
	printf("Target acquired (%d, %d)\n", pos.x, pos.y);
	if (grid[0].HitGrid(pos) == -1)
		GameComputer(pos);
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (player->getShip(i)->getHealth() == dead)
			{
				UpdateGrid(UI.HitColor, player->getShip(i)->getHitbox(), 0);
			}
		}
	}
}

//======================================================================================//
//								     Checkers		   								    //
//======================================================================================//

/*
* SelectedShip - Updates the selected ship by the player for the prep phase.
*/
void GameSystem::SelectedShip()
{
	Vector2i pos = Mouse::getPosition(*game_window);
	cout << pos.x << " " << pos.y << endl;
	if (pos.x < 1500 && pos.x > 1010 && pos.y < 327 && pos.y > 233)
	{
		player->setSelected('C');
		carrier.setColor(UI.GridColor);
		battleship.setColor(Color::White);
		cruiser.setColor(Color::White);
		sub.setColor(Color::White);
		warship.setColor(Color::White);
		setString("Moving Your Carrier...");
	}
	else if (pos.x < 1384 && pos.x > 1027 && pos.y < 407 && pos.y > 369)
	{
		player->setSelected('B');
		carrier.setColor(Color::White);
		battleship.setColor(UI.GridColor);
		cruiser.setColor(Color::White);
		sub.setColor(Color::White);
		warship.setColor(Color::White);
		setString("Moving Your Battleship...");
	}
	else if (pos.x < 1291 && pos.x > 1038 && pos.y < 509 && pos.y > 487 || pos.x < 1205 && pos.x > 1146 && pos.y < 509 && pos.y > 445)
	{
		player->setSelected('c');
		carrier.setColor(Color::White);
		battleship.setColor(Color::White);
		cruiser.setColor(UI.GridColor);
		sub.setColor(Color::White);
		warship.setColor(Color::White);
		setString("Moving Your Cruiser...");
		cout << "SELECTED CRUISER\n";
	}
	else if (pos.x < 1269 && pos.x > 1014 && pos.y < 610 && pos.y > 578)
	{
		player->setSelected('S');
		carrier.setColor(Color::White);
		battleship.setColor(Color::White);
		cruiser.setColor(Color::White);
		sub.setColor(UI.GridColor);
		warship.setColor(Color::White);
		setString("Moving Your Submarine...");
		cout << "SELECTED SUBMARINE\n";
	}
	else if (pos.x < 1173 && pos.x > 1010 && pos.y < 672 && pos.y > 648)
	{
		player->setSelected('W');
		carrier.setColor(Color::White);
		battleship.setColor(Color::White);
		cruiser.setColor(Color::White);
		sub.setColor(Color::White);
		warship.setColor(UI.GridColor);
		setString("Moving Your Warship...");
	}
}

int GameSystem::CheckWinner()
{
	if (player->getState() == dead)
	{
		setString("That Was Close Commander, We Will Get Them Next Time.");
		return 1;
	}
	if (computer->getState() == dead)
	{
		setString("We Won Commander, The Enemy's Fleet Is Destroyed.");
		return -1;
	}
	return 0;
}

Vector2i GameSystem::getGridPos()
{
	Vector2i pos = Mouse::getPosition(*game_window);
	int x = pos.x - UI.player2->x;
	int y = pos.y - UI.player1->y;
	int col = -1, row = -1;
	if (x < 295 && x > 0 && y < 295 && y > 0)
	{
		int c = (x / 30);
		int r = (y / 30);
		if ((x - c * 5) - (c * 25) < 25 * 25 && (x - c * 5) - (c * 25) > 0)
			col = c;
		if ((x - r * 5) - (r * 25) < 25 * 25 && (y - r * 5) - (r * 25) > 0)
			row = r;
	}
	return Vector2i(row, col);
}

bool GameSystem::OpenedMenu()
{
	Vector2i pos = Mouse::getPosition(*game_window);
	if (pos.x > 1490 && pos.x < 1535 && pos.y > 40 && pos.y < 82)
		return true;
	return false;
}

void GameSystem::Execute()
{
	PrepPhase();
}