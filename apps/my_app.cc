// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "../src/board.h"

#include <cinder/app/App.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/Font.h>
#include <cinder/Vector.h>
#include <algorithm>
#include <chrono>
#include <string>
#include <gflags/gflags.h>
#include <cinder/gl/texture.h>

DECLARE_string(playerName);
DECLARE_int32(width);
DECLARE_int32(height);
DECLARE_int32(amount_of_lives);

namespace myapp {
    using cinder::app::KeyEvent;
    using cinder::Color;
    using cinder::ColorA;
    using cinder::Rectf;
    using cinder::app::KeyEvent;
    using std::chrono::duration_cast;
    using std::chrono::seconds;
    using std::chrono::system_clock;
    using std::string;
    using cinder::TextBox;
    //change to string
    const char kNormalFont[] = "Papyrus";

 MyApp::MyApp() :
 width(FLAGS_width),
 height(FLAGS_height),
 playerName(FLAGS_playerName),
 amount_of_lives(FLAGS_amount_of_lives),
 menu {FLAGS_playerName, FLAGS_amount_of_lives, FLAGS_width, FLAGS_height} { }

void MyApp::setup() {
    background = cinder::gl::Texture2d::create(loadImage(loadAsset("backg.jpg")));
    gif_example = cinder::ciAnimatedGif::create(loadAsset("source.gif"));
    //user_player = new mylibrary::Player(playerName, amount_of_lives, width, height);
    //computer_player = new mylibrary::Player("Computer", amount_of_lives, width, height);
}

void MyApp::update() {

     if (menu.user_player_instance->getShips().size() == 0 && menu.computer_player_instance->getShips().size() == 0) {
         state_ = GameState::kPickingShips;
     }

    if (state_ == GameState::kPickingShips) {
        menu.PlaceRandomShips(menu.computer_player_instance);
        DrawPickingShips();

        if (menu.computer_player_instance->getShips().size() == amount_of_lives && menu.user_player_instance->getShips().size() == amount_of_lives) {
            state_ = GameState::kShooting;
        }
    }


    if (menu.user_player_instance->getShips().size() == 0|| menu.computer_player_instance->getShips().size() == 0) {
       state_ = GameState::kGameOver;
    }



     if (state_ == GameState::kShooting) {
         //draw instructions to shoot
         int computer_shot_col = menu.FindRandomRowOrCol(0);
         int computer_shot_row = menu.FindRandomRowOrCol(1);
         menu.computer_player_instance->Attacked(computer_shot_col, computer_shot_row);
     }
     //Menu menu(user_player, computer_player, amount_of_lives, width, height);
    //menu.PlayGame();
 }


void MyApp::draw() {

    cinder::gl::color(Color::white());
    cinder::gl::draw(background, getWindowBounds());
    DrawBoard();

    if (state_ == GameState::kPickingShips) {
        DrawPickingShips();
    }

    if (state_ == GameState::kShooting) {
        DrawShootingInstructions();
    }
    //gif_example->draw();
}


    void MyApp::keyDown(KeyEvent event) { }


template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
                   const cinder::vec2& loc) {
        cinder::gl::color(color);

        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font(kNormalFont, 30))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text);

        const auto box_size = box.getSize();
        const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
}

void MyApp::mouseDown( cinder::app::MouseEvent event ) {
    if (event.isRight() && event.isShiftDown()) {

        auto mMouseLoc = event.getPos();
        mouse_x_ = mMouseLoc.x;
        mouse_y_ = mMouseLoc.y;
        std::cout << "Mouse location: " << mMouseLoc << std::endl;

        if (state_ == GameState::kPickingShips) {
            GatheringXLocationUser();
            GatheringYLocationUser();
            menu.PlacePlayerShips(menu.user_player_instance, user_x, user_y);
        }

        if (state_ == GameState::kShooting) {
            GatheringXLocationUser();
            GatheringYLocationUser();
            menu.user_player_instance->Attacked(user_x, user_y);
        }
        //console() << "Special thing happened!" << std::endl;


        //GatheringXLocationUser();
        //std::cout << "X quantity " << x << std::endl;
        //GatheringYLocationUser();
        //std::cout << "Y quantity " << y << std::endl;
    }

}

void MyApp::GatheringYLocationComputer() {
    for (int i = 130; i <= 365; i++) {
        for (int j = 130; j < 145; j++) {
            if (j == mouse_y_) {
                computer_y = 0;
            }
        }
        for (int j = 160; j <= 175; j++) {
            if (j == mouse_y_) {
                computer_y = 1;
            }
        }
        for (int j = 190; j <= 205; j++) {
            if (j == mouse_y_) {
                computer_y = 2;
            }
        }
        for (int j = 220; j <= 235; j++) {
            if (j == mouse_y_) {
                computer_y = 3;
            }
        }
        for (int j = 250; j <= 265; j++) {
            if (j == mouse_y_) {
                computer_y = 4;
            }
        }
        for (int j = 280; j <= 295; j++) {
            if (j == mouse_y_) {
                computer_y = 5;
            }
        }
        for (int j = 310; j <= 325; j++) {
            if (j == mouse_y_) {
                computer_y = 6;
            }
        }
        for (int j = 340; j <= 365; j++) {
            if (j == mouse_y_) {
                computer_y = 7;
            }
        }
    }
}

    void MyApp::GatheringYLocationUser() {
        for (int i = 520; i <= 740; i++) {
            for (int j = 520; j < 535; j++) {
                if (j == mouse_y_) {
                    user_y = 0;
                }
            }
            for (int j = 550; j <= 565; j++) {
                if (j == mouse_y_) {
                    user_y = 1;
                }
            }
            for (int j = 580; j <= 595; j++) {
                if (j == mouse_y_) {
                    user_y = 2;
                }
            }
            for (int j = 610; j <= 625; j++) {
                if (j == mouse_y_) {
                    user_y = 3;
                }
            }
            for (int j = 640; j <= 655; j++) {
                if (j == mouse_y_) {
                    user_y = 4;
                }
            }
            for (int j = 670; j <= 685; j++) {
                if (j == mouse_y_) {
                    user_y = 5;
                }
            }
            for (int j = 700; j <= 715; j++) {
                if (j == mouse_y_) {
                    user_y = 6;
                }
            }
            for (int j = 730; j <= 745; j++) {
                if (j == mouse_y_) {
                    user_y = 7;
                }
            }
        }
    }

    void MyApp::GatheringXLocationUser() {
        for (int i = 485; i <= 725; i++) {
            for (int j = 485; j <=515; j++) {
                if (j == mouse_x_) {
                    user_x = 0;
                }
            }
            for (int j = 516; j <= 545; j++) {
                if (j == mouse_x_) {
                    user_x = 1;
                }
            }
            for (int j = 546; j <= 575; j++) {
                if (j == mouse_x_) {
                    user_x = 2;
                }
            }
            for (int j = 576; j <= 605; j++) {
                if (j == mouse_x_) {
                    user_x = 3;
                }
            }
            for (int j = 606; j <= 635; j++) {
                if (j == mouse_x_) {
                    user_x = 4;
                }
            }
            for (int j = 636; j <= 655; j++) {
                if (j == mouse_x_) {
                    user_x = 5;
                }
            }
            for (int j = 666; j <= 695; j++) {
                if (j == mouse_x_) {
                    user_x = 6;
                }
            }
            for (int j = 696; j <= 725; j++) {
                if (j == mouse_x_) {
                    user_x = 7;
                }
            }
        }
    }

void MyApp::GatheringXLocationComputer() {
    for (int i = 115; i <= 310; i++) {
        for (int j = 115; j <=145; j++) {
            if (j == mouse_x_) {
                computer_x = 0;
            }
        }
        for (int j = 146; j <= 175; j++) {
            if (j == mouse_x_) {
                computer_x = 1;
            }
        }
        for (int j = 176; j <= 205; j++) {
            if (j == mouse_x_) {
                computer_x = 2;
            }
        }
        for (int j = 206; j <= 235; j++) {
            if (j == mouse_x_) {
                computer_x = 3;
            }
        }
        for (int j = 236; j <= 265; j++) {
            if (j == mouse_x_) {
                computer_x = 4;
            }
        }
        for (int j = 266; j <= 295; j++) {
            if (j == mouse_x_) {
                computer_x = 5;
            }
        }
        for (int j = 296; j <= 325; j++) {
            if (j == mouse_x_) {
                computer_x = 6;
            }
        }
        for (int j = 326; j <= 355; j++) {
            if (j == mouse_x_) {
                computer_x = 7;
            }
        }
    }
}


template <typename C>
void PrintBackground(const C& color, const cinder::ivec2& size) {
    cinder::gl::color(color);
    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2-350.0f,
                                      cinder::app::getWindowHeight()/2-350.0f,
                                      cinder::app::getWindowWidth()/2-30.0f,
                                      cinder::app::getWindowHeight()/2-30.0f ) );

    size_t row = 0;
    PrintText("User", Color::black(), size, {cinder::app::getWindowCenter().x + (++row) * 180,
                                        cinder::app::getWindowCenter().y + (++row) * 30});
    PrintText("Computer", color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                    cinder::app::getWindowHeight() / 2-325.0f});
    PrintText("Instructions:", color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                            cinder::app::getWindowCenter().y + (++row) * 19});

    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2+30.0f,
                                        cinder::app::getWindowHeight()/2+30.0f,
                                        cinder::app::getWindowWidth()/2+350.0f,
                                        cinder::app::getWindowHeight()/2+350.0f ) );

    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2-350.0f,
                                        cinder::app::getWindowHeight()/2+30.0f,
                                        cinder::app::getWindowWidth()/2-30.0f,
                                        cinder::app::getWindowHeight()/2+350.0f ) );

}


void MyApp::DrawBoard() {
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::white();

        PrintText("~Battleship~", color, size, center);
        PrintBackground(color, size);
        ComputerPrintBoard();
        UserPrintBoard();
}

void MyApp::DrawPickingShips() {
     std::string text = "U can place up to  "  +std::to_string(amount_of_lives) +" ships";
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {300, 0};
        const Color color = Color::white();
        size_t row = 0;
        PrintText(text, color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});
 }

    void MyApp::DrawShootingInstructions() {
        std::string text = "Click where U would like to shoot";
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {300, 0};
        const Color color = Color::white();
        size_t row = 0;
        PrintText(text, color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                      cinder::app::getWindowCenter().y + (++row) * 100});
    }

void MyApp::ComputerPrintBoard() {
    mylibrary::Board* board = new mylibrary::Board(width, height);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::white();
    int horizontal_location_numbering = 270.0f;

    for (int i{0}; i < width; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering, cinder::app::getWindowHeight() / 2 - 290.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = 270.0f;
    int vertical_location_in_grid = 250.0f;

    for (int row{0}; row < height; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width; col++) {
            PrintText(board->grid[col][row], color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = 270.0f;
    }
}

void MyApp::UserPrintBoard() {
    mylibrary::Board* board = new mylibrary::Board(width, height);
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {50, 50};
    const Color color = Color::black();
    int horizontal_location_numbering = -100;

    for (int i{0}; i < width; i++) {
        string str = std::to_string(i);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_numbering, cinder::app::getWindowHeight() / 2 + 100.0f});
        horizontal_location_numbering = horizontal_location_numbering - 30;
    }

    int horizontal_location_in_grid = -100.0f;
    int vertical_location_in_grid = -140.0f;

    for (int row{0}; row < height; row++) {
        string str= std::to_string(row);
        PrintText(str, color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid - 40, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
        for (int col{0}; col < width; col++) {
            PrintText(board->grid[col][row], color, size, {cinder::app::getWindowWidth() /2 - horizontal_location_in_grid, cinder::app::getWindowHeight() / 2 - vertical_location_in_grid});
            horizontal_location_in_grid = horizontal_location_in_grid - 30;
        }
        vertical_location_in_grid = vertical_location_in_grid - 30;
        horizontal_location_in_grid = -100.0f;
    }
 }

    void MyApp::TakingInStringInput(std::string printing_string) {
        printing_string_ = printing_string;
        std::cout << printing_string << std::endl;
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::white();
        PrintText(printing_string, color, size, center);

 }


}  // namespace myapp
