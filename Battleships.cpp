// Battleships.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI/Main_Menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(_WIDTH_, _HEIGHT_), "Battleships");
    //window.setFramerateLimit();
    MainMenu menu(window);
    menu.Execute();
    UI.clean();
}
