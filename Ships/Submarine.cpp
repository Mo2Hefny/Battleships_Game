#include "Submarine.h"

Submarine::Submarine()
{
	// Setup hitbox
	AddToHitbox(Vector2i(0, 0));
	AddToHitbox(Vector2i(0, 1));
	AddToHitbox(Vector2i(0, 2));
}