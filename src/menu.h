//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#ifndef FINALPROJECT_MENU_H
#define FINALPROJECT_MENU_H


#include "player.h"

class Menu {
public:
    // Constructor
    Menu(Player* user_player, Player* computer_player, int lives, int width, int height);

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

    std::string playerName;
    //vector of points
    std::vector<Points> points;
    int width;
    int height;
    int amountOfLives;

// Driver for the game
void PlayGame();

private:
    // Board information


    // Players for the game
    Player *user_player_instance;
    Player *computer_player_instance;

    // Finishes game by resetting pointers
    void FinishGame();

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
