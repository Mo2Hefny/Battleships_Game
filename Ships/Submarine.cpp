#include "Submarine.h"

Submarine::Submarine()
{
	// Setup hitbox
	AddToHitbox(Vector2i(-1, 0));
	AddToHitbox(Vector2i(1, 0));
	AddToHitbox(Vector2i(2, 0));
}