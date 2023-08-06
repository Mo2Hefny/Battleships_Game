#include "Carrier.h"

Carrier::Carrier()
{
	// Setup hitbox
	AddToHitbox(Vector2i(-1, 0));
	AddToHitbox(Vector2i(1, 0));
	AddToHitbox(Vector2i(2, 0));
	AddToHitbox(Vector2i(3, 0));
	AddToHitbox(Vector2i(4, 0));
}