//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#ifndef FINALPROJECT_MENU_H
#define FINALPROJECT_MENU_H


#include "player.h"

class Menu {
public:
    // Constructor
    Menu();

    // Destructor
    ~Menu();

    // Asks player for the amount of players and creates the player objects
    void setGameUp();

    struct Points {
        Points(int x, int y) : x{x}, y{y} {};

        int x;
        int y;
    };



    std::vector<Points> points;

private:
    // Board information
    int width;
    int height;
    int amountOfLives;

    // Players for the game
    Player *playerOne;
    Player *playerTwo;

    // Finishes game by resetting pointers
    void finishGame();

    // Plays through a turn for a single player game
    void singlePlayer();

    // Puts ships on the computers board for each live they have
    void placeRandomShips(Player *p);

    // Prints name, lives and board for given player
    void printPlayerInfo(Player *p);

    void placePlayerShips(Player *p);

    int findRandomRowOrCol(int num);
};


#endif //FINALPROJECT_MENU_H
