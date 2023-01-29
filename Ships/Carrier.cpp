#include "Carrier.h"

Carrier::Carrier(RenderWindow& window) : Ship(window)
{
	width = height = 0.2;
	img.loadFromFile(".\\Images\\Carrier.png");
	getSprite().setTexture(img);
	//sprite.setPosition(UI, UI.player1->y);
	getSprite().setScale(width, height);
	hitbox.push_back(Vector2i(0, 0));
	hitbox.push_back(Vector2i(0, 1));
	hitbox.push_back(Vector2i(0, 2));
	hitbox.push_back(Vector2i(0, 3));
	hitbox.push_back(Vector2i(0, 4));
}