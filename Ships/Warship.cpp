#include "Warship.h"

Warship::Warship(RenderWindow& window) : Ship(window)
{
	width = height = 0.2;
	img.loadFromFile(".\\Images\\Warship.png");
	getSprite().setTexture(img);
	getSprite().setScale(width, height);

	hitbox.push_back(Vector2i(0, 0));
	hitbox.push_back(Vector2i(0, 1));
}