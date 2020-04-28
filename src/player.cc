//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "player.h"
#include <utility>

namespace mylibrary {
    Player::Player(std::string name, int lives, int width, int height) :
            name{std::move(name)}, lives{lives} {
        grid = new Board(width, height);
    }


    Player::~Player() {
        delete grid;
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
        if (col > grid->GetWidth() || col < 0 ||
            row > grid->GetHeight() || row < 0) {
            return -1;
        }

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


    void Player::PrintBoard() {
        grid->Print();
    }

    const std::vector<Player::Ship> &Player::getShips() const {
        return ships;
    }
}