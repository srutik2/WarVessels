// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_
#include "/Users/srutikamarajugadda/Desktop/cinder/myproj/final-project-srutik2/src/menu.h"
#include <cinder/app/App.h>
#include <cinder/gl/texture.h>
#include "ciAnimatedGif.h"
#include "../src/player.h"
#include "../src/board.h"

namespace myapp {

class MyApp : public cinder::app::App {

 public:
    enum class GameState {
        kShooting,
        kPickingShips,
        kUserWinner,
        kComputerWinner
    };

    enum class Shooting {
        kUserAttacked,
        kComputerAttacked,
        kNoOneAtttacked
    };

    Shooting state__ = Shooting::kNoOneAtttacked;
    GameState state_ = GameState::kPickingShips;
    int mouse_x_;
    int mouse_y_;
    int count_;
    bool someone_won;
    MyApp();
    const int width;
    const int height;
    const std::string playerName;
    const int amount_of_lives;
    int general_location_x_computer;
    int general_location_x_user;
    int general_location_y_user;
    int general_location_y_computer;
    void DrawHitOrMiss(char c);
  void setup() override;
    char hit_or_not;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  cinder::gl::Texture2dRef background;
  void DrawBoard();
  //void ComputerPrintBoard();
  cinder::ciAnimatedGifRef gif_example;
    void mouseDown( cinder::app::MouseEvent event );
    void GatheringYLocationComputer();
    void GatheringXLocationUser(int col);
    void GatheringXLocationComputer();
    void DrawPickingShips();
    void DrawShootingInstructions();
    void GatheringYLocationUser(int row);
    void DrawWinningScreen();
    int user_x;
    int user_y;
    int computer_x;
    int computer_y;
    int x;
    int y;
    bool computer_attacked;
    bool user_attacked;
    void ComputerPrintBoard();
    void UserPrintBoard();
    void TakingInStringInput(std::string printing_string);
    std::string printing_string_;
    mylibrary::Player *user_player;
    mylibrary::Player *computer_player;
    void ResetGame();
    struct Points {
        Points(int x, int y, std::string s) : x{x}, y{y}, s{s} {};

        int x;
        int y;
        std::string s;
    };
    std::vector<Points> points;
    std::map<std::vector<Points>, char> points_and_character;
private:
    mylibrary::Menu menu;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
