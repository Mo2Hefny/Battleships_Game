#ifndef _DEF_
#define _DEF_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <MMSystem.h.>
#include <fstream>

#define	_WIDTH_	1600	
#define _HEIGHT_ 900
#define _WAIT_ 1500

__declspec(selectany) //This line to prevent "redefinition error"

int MUSIC_VOLUME = 50;

__declspec(selectany) //This line to prevent "redefinition error"

int VOLUME = 50;

using namespace sf;

enum PlayState
{
	menu,
	prep,
	game,
	closed
};

enum PlayerState
{
	dead,
	alive
};

enum OptionMenu
{
	sound,

	closed_op
};

enum Direction
{
	horizontal,
	vertical
};

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Settings
{
	Vector2i* player1 = new Vector2i(80, 220);
	Vector2i* player2 = new Vector2i(560, 220);
	Vector2i* main_menu = new Vector2i(120, 220);
	int Width = 1600;
	int Height = 900;
	Color Sections = Color(255, 255, 255, 70);
	Color PopUps = Color(111, 111, 111, 215);
	Color GridColor = Color(255, 255, 255, 128);
	Color Player_theme = Color(0, 255, 255, 200);
	Color Computer_theme = Color(255, 0, 0, 200);
	Color TextColor = Color(255, 255, 255, 200);
	Color Secondary = Color(192, 192, 192, 170);
	Color HitColor = Color(235, 33, 46, 150);
	Color HitColorShots = Color(247, 13, 26, 170);
	Color MissColorShots = Color(111, 111, 111, 170);
	Color ShipColor = Color(0, 195, 227, 150);
	Color ShipColorSelected = Color(48, 197, 255, 227);
	PlayState mode = prep;
	void clean()
	{
		delete player1, player2, main_menu;
	}

}UI;

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Sounds
{
	Music Main_music, Game_music;
	SoundBuffer barrierB, explosionB, explosion_shipB, hoverB, menuB, moveB, selectB, shotHB, shotLB, rotateB;
	Sound barrier, explosion, explosion_ship, hover, open_menu, move, select, shotH, shotL, rotate;
	int oldVolume, oldMusic;
	UI_Sounds()
	{
		UI_s.Main_music.openFromFile(".\\Sounds\\main_music.wav");
		UI_s.Main_music.setLoop(true);

		barrierB.loadFromFile(".\\Sounds\\barrier.wav");
		barrier.setBuffer(barrierB);

		explosionB.loadFromFile(".\\Sounds\\explosion.wav");
		explosion.setBuffer(explosionB);

		explosion_shipB.loadFromFile(".\\Sounds\\explosion_ship.wav");
		explosion_ship.setBuffer(explosion_shipB);

		hoverB.loadFromFile(".\\Sounds\\hover.wav");
		hover.setBuffer(hoverB);

		menuB.loadFromFile(".\\Sounds\\menu.wav");
		open_menu.setBuffer(menuB);
		
		moveB.loadFromFile(".\\Sounds\\move.wav");
		move.setBuffer(moveB);

		rotateB.loadFromFile(".\\Sounds\\rotate.wav");
		rotate.setBuffer(rotateB);

		selectB.loadFromFile(".\\Sounds\\select.wav");
		select.setBuffer(selectB);

		shotHB.loadFromFile(".\\Sounds\\shot_heavy.wav");
		shotH.setBuffer(shotHB);

		shotLB.loadFromFile(".\\Sounds\\shot_light.wav");
		shotL.setBuffer(shotLB);

		setSFXVolume(VOLUME);
		setMusicVolume(MUSIC_VOLUME);
	}
	void setSFXVolume(int vol)
	{
		oldVolume = VOLUME;
		VOLUME = vol;
		barrier.setVolume(vol);
		explosion.setVolume(vol);
		explosion_ship.setVolume(vol);
		hover.setVolume(vol);
		open_menu.setVolume(vol);
		move.setVolume(vol);
		rotate.setVolume(vol);
		select.setVolume(vol);
		shotH.setVolume(vol);
		shotL.setVolume(vol);
	}
	void setMusicVolume(int vol)
	{
		oldMusic = MUSIC_VOLUME;
		MUSIC_VOLUME = vol;
		Main_music.setVolume(vol);
	}
}UI_s;

#endif