#include "Battleship.h"

Battleship::Battleship()
{
	// Setup hitbox
	AddToHitbox(Vector2i(0, 0));
	AddToHitbox(Vector2i(0, 1));
	AddToHitbox(Vector2i(0, 2));
	AddToHitbox(Vector2i(0, 3));
}