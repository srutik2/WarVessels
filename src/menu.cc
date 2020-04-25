//
// Created by Sruti Kamarajugadda on 4/19/20.
//

#include "menu.h"
#include <iostream>


Menu::Menu(Player *user_player, Player *computer_player, int lives, int width, int height) :
user_player_instance{user_player}, computer_player_instance{computer_player}, amountOfLives(lives), width(width), height(height) { }


Menu::~Menu() { }

/*
void Menu::SetGameUp() {
    std::cout << "~~~You are playing Battleship!~~~" << std::endl;

    std::cout << "Lives: ";
    std::cin >> amountOfLives;
    std::cout << "Board width: ";
    std::cin >> width;
    std::cout << "Board height: ";
    std::cin >> height;
    std::cout << "Player one name: ";
    std::cin >> playerName;

    user_player_instance = new Player(playerName, amountOfLives, width, height);
    computer_player_instance = new Player("Computer", amountOfLives, width, height);
    PlayGame();
}

*/
void Menu::FinishGame() {
    delete user_player_instance;
    delete computer_player_instance;
}


void Menu::PlayGame() {
    std::cout << "Goal is to destroy all the "
                 "computers battleships" << std::endl;
    std::cout << "Example input \"0 3\" will shoot at "
                 "column 0, row 3" << std::endl << std::endl;

    PlacePlayerShips(user_player_instance);
    PlaceRandomShips(computer_player_instance);
    PrintPlayerInfo(computer_player_instance);

    while (computer_player_instance->GetLives() > 0 && user_player_instance->GetLives() > 0) {
        std::cout << "Shoot at: ";
        int user_col_shot, user_row_shot;
        std::cin >> user_col_shot >> user_row_shot;
        points.emplace_back(user_col_shot, user_row_shot);
        computer_player_instance->Attacked(user_col_shot, user_row_shot);

        int computer_col_shot = 0;
        int computer_row_shot = 1;
        computer_col_shot = FindRandomRowOrCol(computer_col_shot);
        computer_row_shot = FindRandomRowOrCol(computer_row_shot);
        user_player_instance->Attacked(computer_col_shot, computer_row_shot);

        std::cout << "opponents's shots " << "colums: " << computer_col_shot << " rows: " << computer_row_shot << std::endl;
        PrintPlayerInfo(computer_player_instance);
        std::cout << "Your battle grid: " << std::endl;
        PrintPlayerInfo(user_player_instance);
    }

    if (computer_player_instance->GetLives() == 0 && user_player_instance->GetLives() == 0) {
        std::cout << "This was a tie!!!" << std::endl;
    } else if (user_player_instance->GetLives() == 0) {
        std::cout << "You lose!!!" << std::endl;
    } else if (computer_player_instance->GetLives() == 0) {
        std::cout << "You win!!!" << std::endl;
    }

    FinishGame();
}

int Menu::FindRandomRowOrCol(int num) {
    if (num == 0) {
        num = (rand() % width);
    } else if (num == 1) {
        num = (rand() % height);
    }
    return num;
}


void Menu::PlaceRandomShips(Player *player) {
    for (int i{0}; i < player->GetLives(); i++) {
        player->AddShip((rand() % width), (rand() % height));
    }
}


void Menu::PlacePlayerShips(Player *player) {
    player->PrintBoard();

    for (int ship_placement_count = 0; ship_placement_count < player->GetLives(); ship_placement_count++) {
        int number_of_picks = player->GetLives() - ship_placement_count;
        std::cout << "pick points to place (you can pick up to " << number_of_picks << ")" <<std::endl;
        int col, row;
        std::cin >> col >> row;

        if (col > width || row > height || col < 0 || row < 0 ) {
            std::cout << col << " " << row << " is not a valid input" << std::endl;
            ship_placement_count = ship_placement_count - 1;
            continue;
        }
        user_player_instance->AddShip(col, row);
        std::cout << "you have placed a ship here: col - " << col << " row - " << row << std::endl;

    }
}


void Menu::PrintPlayerInfo(Player *p) {
    std::cout << "--------------------" << std::endl <<
              p->GetName() << std::endl << "Lives: " <<
              p->GetLives() << std::endl;
    p->PrintBoard();
}
