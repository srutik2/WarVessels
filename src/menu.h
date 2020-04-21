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
    void SetGameUp();

    //struct of points
    struct Points {
        Points(int x, int y) : x{x}, y{y} {};

        int x;
        int y;
    };

    //vector of points
    std::vector<Points> points;

private:
    // Board information
    int width;
    int height;
    int amountOfLives;

    // Players for the game
    Player *user_player;
    Player *computer_player;

    // Finishes game by resetting pointers
    void FinishGame();

    // Driver for the game
    void PlayGame();

    // Puts ships on the computers board for each live they have
    void PlaceRandomShips(Player *player);

    // Prints name, lives and board for given player
    void PrintPlayerInfo(Player *p);

    //user inputs where the ships reside
    void PlacePlayerShips(Player *player);

    //where the random computer ships are
    int FindRandomRowOrCol(int num);
};


#endif //FINALPROJECT_MENU_H
