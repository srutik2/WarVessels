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

MyApp::MyApp() { }


void MyApp::setup() {
    background = cinder::gl::Texture2d::create(loadImage(loadAsset("backg.jpg")));
    gif_example = cinder::ciAnimatedGif::create(loadAsset("spongebob.gif"));
}


void MyApp::update() { }


void MyApp::draw() {
    cinder::gl::color(Color::white());
    cinder::gl::draw(background, getWindowBounds());
    DrawBoard();
    gif_example->draw();
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


template <typename C>
void PrintBackground(const C& color, const cinder::ivec2& size) {
    cinder::gl::color(color);
    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2-350.0f,
                                      cinder::app::getWindowHeight()/2-350.0f,
                                      cinder::app::getWindowWidth()/2-30.0f,
                                      cinder::app::getWindowHeight()/2-30.0f ) );

    size_t row = 0;
    PrintText("Computer", color, size, {cinder::app::getWindowCenter().x + (++row) * 180,
                                        cinder::app::getWindowCenter().y + (++row) * 30});
    PrintText("User", color, size, {cinder::app::getWindowWidth() /2 - 180.0f,
                                    cinder::app::getWindowHeight() / 2-325.0f});

    cinder::gl::drawStrokedRect( Rectf( cinder::app::getWindowWidth()/2+30.0f,
                                        cinder::app::getWindowHeight()/2+30.0f,
                                        cinder::app::getWindowWidth()/2+350.0f,
                                        cinder::app::getWindowHeight()/2+350.0f ) );
}


void MyApp::DrawBoard() {
        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::white();

        PrintText("~Battleship~", color, size, center);
        PrintBackground(color, size);
        PrintBoard();
}


void MyApp::PrintBoard() {
    int width = 8;
    int height = 8;

    Board* board = new Board(width, height);
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

}  // namespace myapp
