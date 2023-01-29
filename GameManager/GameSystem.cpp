#include "GameSystem.h"
#include "../Ships/Carrier.h"
#include "../Ships/Battleship.h"
#include "../Ships/Cruiser.h"
#include "../Ships/Submarine.h"
#include "../Ships/Warship.h"

GameSystem::GameSystem(int width, int height, RenderWindow& window)
{
	//Pointer to window
	game_window = &window;

	//Set Background
	PBackground_img.loadFromFile(".\\Images\\Load.jpg");
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

	//Display Text
	Players_name[0].setFont(font);
	Players_name[0].setString("Player");
	Players_name[0].setCharacterSize(50);
	Players_name[0].setFillColor(UI.Player_theme);
	Players_name[0].setPosition(UI.player1->x, UI.player1->y - 80);

	Players_name[1].setFont(font);
	Players_name[1].setString("Computer");
	Players_name[1].setCharacterSize(50);
	Players_name[1].setFillColor(UI.Computer_theme);
	Players_name[1].setPosition(UI.player2->x, UI.player1->y - 80);

	setMode(prep);
}

//======================================================================================//
//								Preparation Phase										//
//======================================================================================//

/*
* PrepPhase - Preparation phase for the gameplay.
*/
void GameSystem::PrepPhase()
{
	player = new Player(*game_window, &grid[0]);
	computer = new Computer(*game_window, &grid[1]);
	PrepUI();

	bool prepping;
	do
	{
		prepping = false;
		computer->PrepPhase();
		computer->resetPlacements();
		for (int i = 0; i < 5; i++)
		{
			if (!computer->setPlacements(computer->getShip(i)->getHitbox()))
			{
				prepping = true;
				break;
			}
		}
	} while (prepping);
	for (int i = 0; i < 5; i++)
	{
		UpdateGrid(UI.HitColor, computer->getShip(i)->getHitbox(), 1);
	}

	while (CurrentMode() == prep)
	{
		sf::Event event;
		while (game_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game_window->close();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Ship* temp = player->getSelected();
				SelectedShip();
				if (player->getSelected() != NULL && temp != player->getSelected())
				{
					player->getSelected()->PrepPhase();
					UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
					
					//game_window->display();
				}
			}
			if (event.type == Event::KeyPressed)
			{
				// The escape key was pressed
				if (event.key.code == sf::Keyboard::Escape)
					setMode(closed);
				if (player->getSelected() != NULL)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveUp();
						UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Down)
					{
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						game_window->display();
						player->getSelected()->MoveDown();
						UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Left)
					{
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveLeft();
						UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::Right)
					{
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->MoveRight();
						UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
					}
					if (event.key.code == sf::Keyboard::R)
					{
						UpdateGrid(UI.GridColor, player->getSelected()->getHitbox());
						player->getSelected()->Rotate();
						UpdateGrid(UI.ShipColor, player->getSelected()->getHitbox());
					}
				}
				
			}
			
		}
	
		game_window->clear();
		draw();
		game_window->display();
		
	}
}
void GameSystem::draw()
{
	if (mode == prep)
	{
		game_window->draw(PBackground);
		game_window->draw(Sections[0]);
		game_window->draw(Sections[1]);
		game_window->draw(carrier);
		game_window->draw(battleship);
		game_window->draw(cruiser);
		game_window->draw(sub);
		game_window->draw(warship);
		game_window->draw(Players_name[0]);
		game_window->draw(Players_name[1]);
		game_window->draw(prep_ships);
		grid[0].draw(0);
		grid[1].draw(1);
	}
}
/*
* PrepUI - Display the UI for the prep phase.
*/
void GameSystem::PrepUI()
{
	Sections[0].setPosition(45, 105);
	Sections[0].setSize(Vector2f(845, 475));
	Sections[0].setFillColor(UI.Sections);

	Sections[1].setPosition(960, 105);
	Sections[1].setSize(Vector2f(585, 670));
	Sections[1].setFillColor(UI.Sections);

	//Display preparation phase text
	prep_ships.setFont(font);
	prep_ships.setString("Deploy Your Ships");
	prep_ships.setCharacterSize(50);
	prep_ships.setFillColor(UI.TextColor);
	prep_ships.setPosition(1000, UI.player1->y - 80);
	

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

}

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
		cout << "SELECTED CARRIER\n";
	}
	else if (pos.x < 1384 && pos.x > 1027 && pos.y < 407 && pos.y > 369)
	{
		player->setSelected('B');
		cout << "SELECTED BATTLESHIP\n";
	}
	else if (pos.x < 1291 && pos.x > 1038 && pos.y < 509 && pos.y > 487 || pos.x < 1205 && pos.x > 1146 && pos.y < 509 && pos.y > 445)
	{
		player->setSelected('c');
		cout << "SELECTED CRUISER\n";
	}
	else if (pos.x < 1269 && pos.x > 1014 && pos.y < 610 && pos.y > 578)
	{
		player->setSelected('S');
		cout << "SELECTED SUBMARINE\n";
	}
	else if (pos.x < 1173 && pos.x > 1010 && pos.y < 672 && pos.y > 648)
	{
		player->setSelected('W');
		cout << "SELECTED WARSHIP\n";
	}
}

bool GameSystem::UpdateGrid(Color& c, vector<Vector2i>& hitbox, int team)
{
	return grid[team].ColorShip(*game_window, c, hitbox);
}

void GameSystem::Execute()
{
	PrepPhase();
}