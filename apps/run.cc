// Copyright (c) 2020 [Sruti Kamarajugadda]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include "menu.h"
#include "gflags/gflags.h"
#include "my_app.h"
#include "../resources/menu.h"

using cinder::app::App;
using cinder::app::RendererGl;

DEFINE_string(playerName, "Abhi", "the name of the user");
DEFINE_int32(width, 2, "the board width_");
DEFINE_int32(height, 2, "the board height_");
DEFINE_int32(amount_of_lives, 4, "the amount of lives in the game");
DEFINE_bool(is_easy_player_strategy, false, "if the user wants to play against the easy player strategy");


namespace myapp {
void ParseArgs(std::vector<std::string>* args) {
    gflags::SetUsageMessage("Play a game of Snake. Pass --helpshort for options.");
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
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
