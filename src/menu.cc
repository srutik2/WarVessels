//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "menu.h"
#include <iostream>
#include "menu.h"

// Constructor
Menu::Menu() : playerOne{nullptr}, playerTwo{nullptr} {

}

// Destructor
Menu::~Menu() {

}

// Asks player for the amount of players and creates the player objects
void Menu::setGameUp() {
    int amountOfPlayers = 0;
    do {
        std::cout << "How many players? 1 or 2: ";
        std::cin >> amountOfPlayers;
    } while (amountOfPlayers != 1 && amountOfPlayers != 2);


    std::cout << "Lives: ";
    std::cin >> amountOfLives;
    std::cout << "Board width: ";
    std::cin >> width;
    std::cout << "Board height: ";
    std::cin >> height;

    std::string playerName;
    std::cout << "Player one name: ";
    std::cin >> playerName;
    playerOne = new Player(playerName, amountOfLives,
                           width, height);

    if (amountOfPlayers > 1) {
        std::cout << "Player two name: ";
        std::cin >> playerName;
        playerTwo = new Player(playerName, amountOfLives,
                               width, height);
    } else {
        playerTwo = new Player("Computer", amountOfLives,
                               width, height);
        singlePlayer();
    }
}

// Finishes game by resetting pointers
void Menu::finishGame() {
    delete playerOne;
    delete playerTwo;
}

// Plays through a turn for a single player game
void Menu::singlePlayer() {
    std::cout << "Goal is to destroy all the "
                 "computers battleships" << std::endl;
    std::cout << "Example input \"0 3\" will shoot at "
                 "column 0, row 3" << std::endl << std::endl;

    placePlayerShips(playerOne);
    placeRandomShips(playerTwo);
    printPlayerInfo(playerTwo);
    bool game_going = true;

    while (playerTwo->GetLives() > 0 && playerOne->GetLives() > 0) {
        std::cout << "Shoot at: ";
        int col, row;
        std::cin >> col >> row;
        points.emplace_back(col,row);
        playerTwo->Attacked(col, row);
        int columns = 0;
        int rows = 1;
        columns = findRandomRowOrCol(columns);
        rows = findRandomRowOrCol(rows);
        playerOne->Attacked(columns, rows);
        std::cout << "opponents's shots " << "colums: " << columns << " rows: " << rows << std::endl;
        printPlayerInfo(playerTwo);
        std::cout << "Your battle grid: " << std::endl;
        printPlayerInfo(playerOne);
    }


    if (playerTwo->GetLives() == 0 && playerOne->GetLives() == 0) {
        std::cout << "This was a tie!!!" << std::endl;
    } else if (playerOne->GetLives() == 0) {
        std::cout << "You lose!!!" << std::endl;
    } else if (playerTwo->GetLives() == 0) {
        std::cout << "You win!!!" << std::endl;
    }

    finishGame();
}

int Menu::findRandomRowOrCol(int num) {
    if (num == 0) {
        num = (rand() % width);
    } else if (num == 1) {
        num = (rand() % height);
    }
    return num;
}

// Puts ships on the computers board for each live they have
void Menu::placeRandomShips(Player *p) {
    for (int i{0}; i < p->GetLives(); i++) {
        p->AddShip((rand() % width), (rand() % height));
    }
}

void Menu::placePlayerShips(Player *p) {
    p->printBoard();
    for (int i = 0; i < p->GetLives(); i++) {
        int number_of_picks = p->GetLives() - i;
        std::cout << "pick points to place (you can pick up to " << number_of_picks << ")" <<std::endl;
        int col, row;
        std::cin >> col >> row;
        if (col > width || row > height || col < 0 || row < 0 ) {
            std::cout << col << " " << row << " is not a vaild input" << std::endl;
            i = i -1;
            continue;
        }

        /*
        for (int i = 0; i < p->getShips().size(); i++) {
            Player::Ship(col, row)* = new Player::Ship
            if (p->getShips().at(i) == Player::Ship(col, row) );

            Ship(int col, int row) : col{col}, row{row} {};
        }
         */

        playerOne->AddShip(col, row);
        std::cout << "you have placed a ship here: col- " << col << " row- " << row << std::endl;

    }
}

// Prints name, lives and board for given player
void Menu::printPlayerInfo(Player *p) {
    std::cout << "--------------------" << std::endl <<
              p->GetName() << std::endl << "Lives: " <<
              p->GetLives() << std::endl;
    p->printBoard();
}
