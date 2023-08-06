#include "Ship.h"

Ship::Ship()
{
	rotation = horizontal;
	row = col = 0;
	health = alive;
}

/*
* PrepPhase - Deploys the ship on the grid in its current position.
*/
void Ship::PrepPhase()
{
	int r = row;
	int c = col;
	if (getRotation() == horizontal)
	{
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = r;
			hitbox[i].x = c++;
		}
	}
	else
	{
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = r++;
			hitbox[i].x = c;
		}
	}
	
}

/*
* MoveUp - Moves the ship upwards in the prepration phase.
*/
void Ship::MoveUp()
{
	// Horizontal
	if (getRotation() == horizontal)
	{
		if (row - 1 < 0)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int r = --row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = r;
		}
	}
	// Vetrical
	else
	{
		if (row - 1 < 0)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int r = --row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = r++;
		}
	}

	UI_s.move.play();		// Play moving sound
}

/*
* MoveDown - Moves the ship downwards in the prepration phase.
*/
void Ship::MoveDown()
{
	// Horizontal
	if (getRotation() == horizontal)
	{
		if (row + 1 > 9)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int r = ++row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = r;
		}
	}
	// Vertical
	else
	{
		if (row + hitbox.size() > 9)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int r = ++row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = r++;
		}
	}

	UI_s.move.play();		// Play moving sound
}

/*
* MoveLeft - Moves the ship to the left in the prepration phase.
*/
void Ship::MoveLeft()
{
	// Horizontal
	if (getRotation() == horizontal)
	{
		if (col - 1 < 0)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int c = --col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = c++;
		}
	}
	// Vertical
	else
	{
		if (col - 1 < 0)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int c = --col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = c;
		}
	}

	UI_s.move.play();		// Play moving sound
}

/*
* MoveRight - Moves the ship to the right in the prepration phase.
*/
void Ship::MoveRight()
{
	// Horizontal
	if (getRotation() == horizontal)
	{
		if (col + hitbox.size() > 9)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int c = ++col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = c++;
		}
	}
	// Vertical
	else
	{
		if (col + 1 > 9)		//Exceeding Grid borders
		{
			UI_s.barrier.play();		// Play movement error sound
			return;
		}
		int c = ++col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = c;
		}
	}

	UI_s.move.play();		// Play moving sound
}

/*
* Rotate - Rotates the ship in the prepration phase.
*/
void Ship::Rotate()
{
	int c = hitbox[0].x;
	int r = hitbox[0].y;

	// Horizontal to Vertical
	if (getRotation() == horizontal)
	{
		if (r + hitbox.size() > 10)			//Rotated vertical ship will exceed the borders
		{
			UI_s.barrier.play();		// Play rotation error sound
			return;
		}
		setRotation(vertical);
		for (int i = 1; i < hitbox.size(); i++)
		{
			hitbox[i].y = ++r;
			hitbox[i].x = c;
		}
	}
	// Vertical to Horizontal
	else
	{
		if (c + hitbox.size() > 10)			//Rotated horizontal ship will exceed the borders
		{
			UI_s.barrier.play();		// Play rotation error sound
			return;
		}
		setRotation(horizontal);
		for (int i = 1; i < hitbox.size(); i++)
		{
			hitbox[i].y = r;
			hitbox[i].x = ++c;
		}
	}

	UI_s.rotate.play();		// Play rotating sound
}

/*
* setRow - Updates the ship's starting row position.
* 
* @param r - the value of the new row.
* 
* @return true on success, false otherwise.
*/
bool Ship::setRow(int r)
{
	if (getRotation() == vertical && (r + hitbox.size() > 10 || r < 0))			//Exceeding Grid borders
		return false;
	else if (getRotation() == horizontal && (r  > 10 || r < 0))			//Exceeding Grid borders
		return false;

	// Updates ship's row
	row = r;
	if (getRotation() == horizontal)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].y = r;
	else if (getRotation() == vertical)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].y = r++;
	return true;
}

/*
* setColumn - Updates the ship's starting column position.
* 
* @param c - the value of the new column.
* 
* @return true on success, false otherwise.
*/
bool Ship::setColumn(int c)
{
	if (getRotation() == horizontal && (c + hitbox.size() > 10 || c < 0))		//Exceeding Grid borders
		return false;
	else if (getRotation() == vertical && (c > 10 || c < 0))		//Exceeding Grid borders
		return false;

	// Updates ship's column
	col = c;
	if (getRotation() == horizontal)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].x = c++;
	else if (getRotation() == vertical)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].x = c;
	return true;
}

/*
* changeHitboxValues - Updates the ship's positions value on grid.
*
* @param value - the new value for each position.
* @param grid - the affected grid.
*/
void Ship::changeHitboxValues(int value, int**& grid)
{ 
	for (auto pos : hitbox)
		grid[pos.y][pos.x] = value;
}