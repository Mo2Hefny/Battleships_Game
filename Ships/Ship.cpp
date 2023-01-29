#include "Ship.h"

Ship::Ship(RenderWindow& window)
{
	game_window = &window;
	position.x = UI.player1->x;
	position.y = UI.player1->y;
	rotation = horizontal;
	row = col = 0;
}

void Ship::PrepPhase()
{
	int c = col;
	for (int i = 0; i < hitbox.size(); i++)
	{
		hitbox[i].x = 0;
		hitbox[i].y = c++;
	}
}

void Ship::MoveUp()
{
	if (getRotation() == horizontal)
	{
		if (row - 1 < 0) return;
		int r = --row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = r;
		}
	}
	else
	{
		if (row - 1 < 0) return;
		int r = --row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = r++;
		}
	}
}

void Ship::MoveDown()
{
	if (getRotation() == horizontal)
	{
		if (row + 1 > 9) return;
		int r = ++row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = r;
		}
	}
	else
	{
		if (row + hitbox.size() > 9) return;
		int r = ++row;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].x = r++;
		}
	}
}

void Ship::MoveLeft()
{
	if (getRotation() == horizontal)
	{
		if (col - 1 < 0) return;
		int c = --col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = c++;
		}
	}
	else
	{
		if (col - 1 < 0) return;
		int c = --col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = c;
		}
	}
}

void Ship::MoveRight()
{
	if (getRotation() == horizontal)
	{
		if (col + hitbox.size() > 9) return;
		int c = ++col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = c++;
		}
	}
	else
	{
		if (col + 1 > 9) return;
		int c = ++col;
		for (int i = 0; i < hitbox.size(); i++)
		{
			hitbox[i].y = c;
		}
	}
}

void Ship::Rotate()
{
	int c = hitbox[0].y;
	int r = hitbox[0].x;
	if (getRotation() == horizontal)
	{
		if (r + hitbox.size() > 10) return;
		setRotation(vertical);
		for (int i = 1; i < hitbox.size(); i++)
		{
			hitbox[i].x = ++r;
			hitbox[i].y = c;
		}
	}
	else
	{
		if (c + hitbox.size() > 10) return;
		setRotation(horizontal);
		for (int i = 1; i < hitbox.size(); i++)
		{
			hitbox[i].x = r;
			hitbox[i].y = ++c;
		}
	}
}

bool Ship::setRow(int r)
{
	if (getRotation() == vertical && (r + hitbox.size() > 10 || r < 0))
		return false;
	else if (getRotation() == horizontal && (r  > 10 || r < 0))
		return false;
	row = r;
	if (getRotation() == horizontal)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].x = r;
	else if (getRotation() == vertical)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].x = r++;
	return true;
}

bool Ship::setColumn(int c)
{
	if (getRotation() == horizontal && (c + hitbox.size() > 10 || c < 0))
		return false;
	else if (getRotation() == vertical && (c > 10 || c < 0))
		return false;
	col = c;
	if (getRotation() == horizontal)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].y = c++;
	else if (getRotation() == vertical)
		for (int i = 0; i < hitbox.size(); i++)
			hitbox[i].y = c;
	return true;
}
