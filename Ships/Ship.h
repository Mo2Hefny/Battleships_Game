#ifndef _SHIPS_
#define _SHIPS_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../UI/Grid.h"

using namespace std;
using namespace sf;

class Ship
{
	Direction rotation;
	PlayerState health;
	vector<Vector2i> hitbox;
	int row, col;

public:
	Ship();
	virtual ~Ship() {}

	// Preparation phase movement
	virtual void PrepPhase();
	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveRight();
	virtual void MoveLeft();
	void Rotate();

	// setters
	void AddToHitbox(Vector2i h) { hitbox.push_back(h); }
	void setRotation(Direction d) { rotation = d; }
	void setHealth(PlayerState mode) { health = mode; }
	bool setRow(int r);
	bool setColumn(int c);

	// getters
	Direction getRotation() const { return rotation; }
	PlayerState getHealth() const { return health; }
	virtual vector<Vector2i>& getHitbox() { return hitbox; }
};

#endif