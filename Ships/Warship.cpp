#include "Warship.h"

Warship::Warship()
{
	// Setup hitbox
	AddToHitbox(Vector2i(0, 0));
	AddToHitbox(Vector2i(0, 1));
}