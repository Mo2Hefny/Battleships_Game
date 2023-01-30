#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < 10; i++)
	{
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
	shot_count = 0;
}

Grid::~Grid()
{
	for (int i = 0; i < shot_count; i++)
	{
		delete shots[i];
	}
}

void Grid::draw(int player)
{
	int x = (player == 0 ) ? UI.player1->x : UI.player2->x, y = UI.player1->y;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			grid[i][j].setPosition(x + j * 30, y + i * 30);
			game_window->draw(grid[i][j]);
		}
	}
	for (int i = 0; i < shot_count; i++)
	{
		game_window->draw(*shots[i]);
	}
}

void Grid::ColorShip(Color& c, vector<Vector2i>& hitbox)
{
	bool empty_space = true;
	for (int i = 0; i < hitbox.size(); i++)
	{
		if (placement[hitbox[i].x][hitbox[i].y] == 0 && c == UI.GridColor)
		{
			grid[hitbox[i].x][hitbox[i].y].setFillColor(c);
		}
		else if (placement[hitbox[i].x][hitbox[i].y] != 0 && c == UI.GridColor && UI.mode == game)
		{
			grid[hitbox[i].x][hitbox[i].y].setFillColor(c);
		}
		else if (placement[hitbox[i].x][hitbox[i].y] != 0 && c == UI.GridColor)
		{
			grid[hitbox[i].x][hitbox[i].y].setFillColor(UI.ShipColor);
		}
		else if (c != UI.GridColor)
		{
			grid[hitbox[i].x][hitbox[i].y].setFillColor(c);
		}
		//window.draw(grid[hitbox[i].x][hitbox[i].y]);
	}
}

int Grid::CheckValidity()
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (placement[i][j] == 0)
				count++;
			if (placement[i][j] != 0 && placement[i][j] != -1)
			{
				return 0;
			}
		}
	}
	if (count == 83)
		return 1;
	return -1;
}

void Grid::setPlacements(vector<Vector2i> hitbox, int mode)
{
	for (int i = 0; i < hitbox.size(); i++)
	{
		int x = hitbox[i].x, y = hitbox[i].y;
		if (mode)	//add ship hitbox
			placement[x][y] -= 1;
		else		//remove ship hitbox
			placement[x][y] = (placement[x][y] + 1 > 0) ? 0 : placement[x][y] + 1;
	}
}

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

int Grid::HitGrid(Vector2i& pos)
{
	int x = pos.x; int y = pos.y;
	int gx = grid[x][y].getPosition().x; int gy = grid[x][y].getPosition().y;
	if (placement[x][y] == 0)
	{
		placement[x][y] = -5;
		shots[shot_count] = new CircleShape;
		shots[shot_count]->setRadius(8);
		shots[shot_count]->setPosition(gx + 4, gy + 4);
		shots[shot_count]->setFillColor(UI.MissColorShots);
		shots[shot_count]->setOutlineThickness(4);
		shots[shot_count]->setOutlineColor(UI.Secondary);
		shot_count++;
		cout << "Miss\n";
		return 0;
	}
	if (placement[x][y] == -1)
	{
		placement[x][y] = -10;
		shots[shot_count] = new CircleShape;
		shots[shot_count]->setRadius(8);
		shots[shot_count]->setPosition(gx + 4, gy + 4);
		shots[shot_count]->setFillColor(UI.HitColorShots);
		shots[shot_count]->setOutlineThickness(4);
		shots[shot_count]->setOutlineColor(UI.Secondary);
		shot_count++;
		cout << "Hit\n";
		return 1;
	}
	return -1;
}