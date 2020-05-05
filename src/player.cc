//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "../resources/player.h"
#include <utility>
#include <iostream>

namespace mylibrary {
Player::Player(std::string name, int lives, int width, int height) : name{std::move(name)}, lives{lives} {
    grid = new Board(width, height);
}


std::string Player::GetName() {
    return name;
}


int &Player::GetLives() {
    return lives;
}


void Player::AddShip(int col, int row) {
    ships.emplace_back(Ship(col, row));
}


int Player::Attacked(int col, int row) {
    if_played = true;
    hit_or_not = false;
        try {
            if (col > grid->GetWidth() || col < 0 || row > grid->GetHeight() || row < 0) {
                throw std::out_of_range("Out of range");
            }
        }
        catch (const std::out_of_range& oor) {
            std::cerr << "Out of Range error: " << oor.what() << '\n';
            return -1;
        }



    for (int i{0}; i < ships.size(); i++) {
        if (col == ships[i].col && row == ships[i].row) {
            grid->Hit(col, row);
            ships[i] = ships[ships.size() - 1];
            ships.pop_back();
            lives--;
            hit_or_not = true;
            return 1;
        }
    }

    grid->Miss(col, row);
    hit_or_not = false;
    return 0;
}


void Player::PrintBoard() {
    grid->Print();
}


const std::vector<Player::Ship> &Player::getShips() const {
    return ships;
}
}