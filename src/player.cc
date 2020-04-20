//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "player.h"
#include "player.h"

#include <utility>

// Constructor
Player::Player(std::string name, int lives, int width, int height) :
        name{std::move(name)}, lives{lives} {
    grid = new Board(width, height);
}

// Destructor
Player::~Player() {
    delete grid;
}

// Returns name of the player
std::string Player::GetName() {
    return name;
}

// Returns number of players lives
int &Player::GetLives() {
    return lives;
}

// Adds a ship to the vector
void Player::AddShip(int col, int row) {
    ships.emplace_back(Ship(col, row));
}

// Player gets "board attacked"
// Returns: -1 = out of bounds, 0 = miss, 1 = hit
int Player::Attacked(int col, int row) {
    if (col > grid->getWidth() || col < 0 ||
        row > grid->getHeight() || row < 0) {
        return -1;
    }


    /*
     * Menu menu;
    for (int i = 0; i < menu.points.size(); i++) {
        menu.point_one = {col, row};
        if (menu.points.at(i) == menu.point_one) {

        }
    }
*/
    for (int i{0}; i < ships.size(); i++) {
        if (col == ships[i].col && row == ships[i].row) {
            grid->Hit(col, row);
            ships[i] = ships[ships.size() - 1];
            ships.pop_back();
            lives--;
            return 1;
        }
    }


    grid->Miss(col, row);
    return 0;
}

// Prints board for current player
void Player::printBoard() {
    grid->Print();
}

const std::vector<Player::Ship> &Player::getShips() const {
    return ships;
}
