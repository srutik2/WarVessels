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
        kGameOver,
    };

    GameState state_ = GameState::kPickingShips;
    int mouse_x_;
    int mouse_y_;
    int count_;
    MyApp();
    const int width;
    const int height;
    const std::string playerName;
    const int amount_of_lives;

  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  cinder::gl::Texture2dRef background;
  void DrawBoard();
  //void ComputerPrintBoard();
  cinder::ciAnimatedGifRef gif_example;
    void mouseDown( cinder::app::MouseEvent event );
    void GatheringYLocationComputer();
    void GatheringXLocationUser();
    void GatheringXLocationComputer();
    void DrawPickingShips();
    void DrawShootingInstructions();
    void GatheringYLocationUser();
    int user_x;
    int user_y;
    int computer_x;
    int computer_y;
    int x;
    int y;
    void ComputerPrintBoard();
    void UserPrintBoard();
    void TakingInStringInput(std::string printing_string);
    std::string printing_string_;
    mylibrary::Player *user_player;
    mylibrary::Player *computer_player;
    void ResetGame();
private:
    mylibrary::Menu menu;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
