#ifndef _SHIPS_
#define _SHIPS_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../DEFS.h"
#include "../UI/Grid.h"

using namespace std;
using namespace sf;

class Ship
{
	RenderWindow* game_window;
	Vector2f position;
	Direction rotation;
	Sprite sprite;
	int row, col;

protected:
	vector<Vector2i> hitbox;
public:
	Ship(RenderWindow&);
	virtual ~Ship() {}

	//Preparation phase movement
	virtual void PrepPhase();
	virtual void MoveUp();
	virtual void MoveDown();
	virtual void MoveRight();
	virtual void MoveLeft();
	void Rotate();

	//setters
	void setPosition(Vector2f pos) { position = pos; }
	void setRotation(Direction d) { rotation = d; }
	bool setRow(int r);
	bool setColumn(int c);

	//getters
	Sprite getSprite() const { return sprite; }
	RenderWindow* getWindow() const { return game_window; }
	Direction getRotation() const { return rotation; }
	virtual vector<Vector2i>& getHitbox() { return hitbox; }
};

#endif