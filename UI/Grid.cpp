#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			grid[i][j].setSize(Vector2f(25, 25));

			//Set color half transparent
			grid[i][j].setFillColor(sf::Color(255, 255, 255, 128));
		}
	}
}

void Grid::draw(RenderWindow& window, Player p)
{
	int x = (p == player ) ? 100 : 600, y = 250;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			grid[i][j].setPosition(x + i * 30, y + j * 30);
			window.draw(grid[i][j]);
		}
	}
}

