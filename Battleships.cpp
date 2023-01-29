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
    //GameSystem game(_WIDTH_, _HEIGHT_, window);
    /*Texture img;
    Sprite s;
    img.loadFromFile(".\\Images\\Battleship.png");
    s.setTexture(img);
    s.setScale(0.25, 0.25);*/
    RectangleShape test;
    test.setSize(Vector2f(25, 25));

    //Set color half transparent
    test.setFillColor(UI.GridColor);
    test.setPosition(200, 200);
    window.draw(test);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                // The escape key was pressed
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Up)
                {
                    test.setFillColor(UI.ShipColor);
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    test.setFillColor(UI.GridColor);
                }

            }
        }

       //window.clear();
        window.draw(test);
        window.display();
    }
    UI.clean();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
