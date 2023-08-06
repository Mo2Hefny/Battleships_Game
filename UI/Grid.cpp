#include "Grid.h"

Grid::Grid()
{
	placement = new int* [10];
	for (int i = 0; i < 10; i++)
	{
		placement[i] = new int[10];
		for (int j = 0; j < 10; j++)
		{
			grid[i][j].setSize(Vector2f(25, 25));

			//Set color half transparent
			grid[i][j].setFillColor(UI.GridColor);
		}
	}
	for (int i = 0; i < 100; i++)
	{
		shots[i] = NULL;
	}
	shot_count = hit = miss = 0;
}

Grid::~Grid()
{
	for (int i = 0; i < shot_count; i++)
	{
		delete shots[i];
	}
}

/*
* draw - Updates the grids.
* 
* @param player - Indicator of the team to draw in the desired position.
*/
void Grid::draw(int player)
{
	int x = (player == 0 ) ? UI.player1->x : UI.player2->x, y = UI.player1->y;
	
	// Draws Grid
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			grid[i][j].setPosition(x + j * 30, y + i * 30);
			game_window->draw(grid[i][j]);
		}
	}
	
	// Draw Shots Fired
	for (int i = 0; i < shot_count; i++)
	{
		game_window->draw(*shots[i]);
	}
}


/*
* ColorShip - Colors the position of the ships blue when alive or red when destroyed.
*
* @param c - New color for the Ship's whom position is given.
* @param hitbox - Location of the Ship's cubes.
*/
void Grid::ColorShip(Color& c, vector<Vector2i>& hitbox)
{
	for (int i = 0; i < hitbox.size(); i++)
	{
		if (placement[hitbox[i].y][hitbox[i].x] == 0 && c == UI.GridColor)
		{
			grid[hitbox[i].y][hitbox[i].x].setFillColor(c);
		}
		else if (placement[hitbox[i].y][hitbox[i].x] != 0 && c == UI.GridColor && UI.mode == game)
		{
			grid[hitbox[i].y][hitbox[i].x].setFillColor(c);
		}
		else if (placement[hitbox[i].y][hitbox[i].x] != 0 && c == UI.GridColor)
		{
			grid[hitbox[i].y][hitbox[i].x].setFillColor(UI.ShipColor);
		}
		else if (c != UI.GridColor)
		{
			grid[hitbox[i].y][hitbox[i].x].setFillColor(c);
		}
	}
}

/*
* CheckValidity - checks if the ships placements are valid to start the game.
* 
* @return 1 if valid, 0 if ships are overlapping, -1 if ships aren't all deployed.
*/
int Grid::CheckValidity()
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (placement[i][j] == 0)		//Empty Cube
				count++;
			if (placement[i][j] != 0 && placement[i][j] != -1)		// Multiple ships on the same cube.
			{
				return 0;
			}
		}
	}
	if (count == 83)		// 17 cubes are occupied.
		return 1;
	return -1;				// less than 17 cubes are occupied.
}

/*
* resetPlacements - resets the grid placements info.
*/
void Grid::resetPlacements()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			placement[i][j] = 0;
		}
	}
}

/*
* setPlacements - updates the grid placements info.
* 
* @param hitbox - Location of the Ship's cubes.
* @param mode - 1 to add, 0 to remove
*/
void Grid::setPlacements(vector<Vector2i> hitbox, int mode)
{
	for (int i = 0; i < hitbox.size(); i++)
	{
		int x = hitbox[i].x, y = hitbox[i].y;
		if (mode)	//add ship hitbox
			placement[y][x] -= 1;
		else		//remove ship hitbox
			placement[y][x] = (placement[y][x] + 1 > 0) ? 0 : placement[y][x] + 1;
	}
}

/*
* HitGrid - adds shots to the grid at the specified location.
*
* @param pos - Position of cube targeted in the grid.
* 
* @return 1 if target is hit, 0 if missed, -1 if error occured.
*/
int Grid::HitGrid(Vector2i& pos)
{
	int x = pos.x; int y = pos.y;
	int gx = grid[y][x].getPosition().x; int gy = grid[y][x].getPosition().y;
	// Hit Target
	if (placement[y][x])
	{
		placement[y][x] = -1;
		shots[shot_count] = new CircleShape;
		shots[shot_count]->setRadius(8);
		shots[shot_count]->setPosition(gx + 4, gy + 4);
		shots[shot_count]->setFillColor(UI.HitColorShots);
		shots[shot_count]->setOutlineThickness(4);
		shots[shot_count]->setOutlineColor(UI.Secondary);
		shot_count++;
		hit++;

		// Terminal Updates
		printf("HIT TARGET --- Misses: %d, Hits: %d\n", miss, hit);
		return 1;
	}

	// Missed Target
	placement[y][x] = -1;
	shots[shot_count] = new CircleShape;
	shots[shot_count]->setRadius(8);
	shots[shot_count]->setPosition(gx + 4, gy + 4);
	shots[shot_count]->setFillColor(UI.MissColorShots);
	shots[shot_count]->setOutlineThickness(4);
	shots[shot_count]->setOutlineColor(UI.Secondary);
	shot_count++;
	miss++;

	// Terminal Updates
	printf("MISSED TARGET --- Misses: %d, Hits: %d\n", miss, hit);
	return 0;
}