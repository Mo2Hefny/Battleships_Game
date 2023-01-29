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
}

bool Grid::ColorShip(RenderWindow& window, Color& c, vector<Vector2i>& hitbox)
{
	bool empty_space = true;
	for (int i = 0; i < hitbox.size(); i++)
	{
		if (grid[hitbox[i].x][hitbox[i].y].getFillColor() == c)
			empty_space = false;
		grid[hitbox[i].x][hitbox[i].y].setFillColor(Color::White);
		grid[hitbox[i].x][hitbox[i].y].setFillColor(c);
		//window.draw(grid[hitbox[i].x][hitbox[i].y]);
	}
	return false;
}

bool Grid::CheckValidity(Color c)
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (grid[i][j].getFillColor() == c)
				count++;
		}
	}
	if (count == 17)
		return true;
	return false;
}

