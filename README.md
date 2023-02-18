# Battleships
## Description
This is a replica of the classic [Battleship](https://en.wikipedia.org/wiki/Battleship_game) board game. This program was written entirely in C++ as a personal project in my learning journey.

## Installation
Clone this repository, open the `Battleship` folder, and launch the `Battleship.exe` application.  
`https://github.com/Mo2Hefny/Battleships_Game`  
  
To launch your executable file in case you played with the code,  open the following path. `x64/Debug/Battleship.exe`.

## Environment
This project was built on Visual Studio using the [SFML](https://www.sfml-dev.org/) library.

## Gameplay
After running the `.sln` file, the title screen should look like this:   

![battleship_main_menu](https://user-images.githubusercontent.com/111001850/216157041-ee831be0-5497-472b-b94e-a64c3e810113.png)

The game currently supports playing **Versus AI** mode only.

### I. Preparation Phase
To place a ship, select it from the _Ships section_ and move it to the desired location with your keyboard. Your AI opponent has already placed his ships.

![image](https://user-images.githubusercontent.com/111001850/216161216-e64ee77d-5715-4688-ab85-d4db3acf40bc.png)

Once you've legally placed all your ships, you can start the game by hitting `Enter`.

### II. Gameplay Phase

The goal is to find and sink all enemy ships before they find and sink all of yours.

![gameplay_phase](https://user-images.githubusercontent.com/111001850/216161813-c58cd1fc-6121-47f5-befb-e3c37b9307f2.png)

Once a player has found and destroyed all 5 enemy ships, the game ends.

#### AI Strategies
The current implementations of various strategies to challenge the player:
- **Random Targeting**: shoots at a random spot till it finds an enemy ship, ***BUT*** it won't target spots that can't hold the smallest still living ship.

![hit_target](https://user-images.githubusercontent.com/111001850/216166236-4648ce6f-52ba-402f-9c6a-37cb89904a63.png)

- **Finishing Ship**: if a ship was found, the AI chooses a random direction to shoot beside the initial hit position till it finds the right path and destroys the ship.

![finish_ship](https://user-images.githubusercontent.com/111001850/216166124-800a5a91-6214-4ff0-b108-ab51ac2a61ef.png)

- **Checking Other Ships**: checks if another ship was hit while destroying and finishing the found ship.

![hit_path](https://user-images.githubusercontent.com/111001850/216166535-b3721f14-6269-4f08-80e7-075a2bb374a9.png)


