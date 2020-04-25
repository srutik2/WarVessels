// Copyright (c) 2020 [Sruti Kamarajugadda]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include "menu.h"
#include "gflags/gflags.h"
#include "my_app.h"
#include "../src/menu.h"

using cinder::app::App;
using cinder::app::RendererGl;
DEFINE_string(playerName, "sruti", "the name of the user");
DEFINE_uint32(width, 7, "the speed (delay) of the game");
DEFINE_uint32(height, 7, "the speed (delay) of the game");
DEFINE_uint32(amount_of_lives, 2, "the speed (delay) of the game");


namespace myapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;


void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
    Player *user_player;
    Player *computer_player;
  user_player = new Player(FLAGS_playerName, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height);
  computer_player = new Player("Computer", FLAGS_amount_of_lives, FLAGS_width, FLAGS_height);
  Menu menu(user_player, computer_player, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height);
  menu.PlayGame();

  //exit(0);
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
