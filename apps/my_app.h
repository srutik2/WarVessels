// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/texture.h>
#include "ciAnimatedGif.h"
#include "../src/player.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
    int mouse_x_;
    int mouse_y_;
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  cinder::gl::Texture2dRef background;
  void DrawBoard();
  void PrintBoard();
  cinder::ciAnimatedGifRef gif_example;
    void mouseDown( cinder::app::MouseEvent event );
    void GatheringYLocation();
    void GatheringXLocation();
    int x;
    int y;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
