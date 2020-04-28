// Copyright (c) 2020 [Sruti Kamarajugadda]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include "menu.h"
#include "gflags/gflags.h"
#include "my_app.h"
#include "../src/menu.h"

using cinder::app::App;
using cinder::app::RendererGl;

DEFINE_string(playerName, "Sruti Kamarajugadda", "the name of the user");
DEFINE_int32(width, 4, "the board width");
DEFINE_int32(height, 4, "the board height");
DEFINE_int32(amount_of_lives, 2, "the amount of lives in the game");


namespace myapp {

    void ParseArgs(std::vector<std::string>* args) {
        gflags::SetUsageMessage(
                "Play a game of Snake. Pass --helpshort for options.");
        int argc = static_cast<int>(args->size());

        std::vector<char*> argvs;
        for (std::string& str : *args) {
            argvs.push_back(&str[0]);
        }

        char** argv = argvs.data();
        gflags::ParseCommandLineFlags(&argc, &argv, true);
    }

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
    std::vector<std::string> args = settings->getCommandLineArgs();
    ParseArgs(&args);
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("My CS 126 Application");
/*
    Player *user_player;
   Player *computer_player;
   user_player = new Player(FLAGS_playerName, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height);
    computer_player = new Player("Computer", FLAGS_amount_of_lives, FLAGS_width, FLAGS_height);
    Menu menu(user_player, computer_player, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height);
    menu.PlayGame();
*/
  //exit(0);
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
