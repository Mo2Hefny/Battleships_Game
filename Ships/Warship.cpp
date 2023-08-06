#include "Warship.h"

Warship::Warship()
{
	// Setup hitbox
	AddToHitbox(Vector2i(-1, 0));
	AddToHitbox(Vector2i(1, 0));
}