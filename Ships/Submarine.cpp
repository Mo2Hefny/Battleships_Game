#include "Submarine.h"

Submarine::Submarine(RenderWindow& window) : Ship(window)
{
	width = height = 0.2;
	img.loadFromFile(".\\Images\\Submarine.png");
	getSprite().setTexture(img);
	getSprite().setScale(width, height);

	hitbox.push_back(Vector2i(0, 0));
	hitbox.push_back(Vector2i(0, 1));
	hitbox.push_back(Vector2i(0, 2));
}