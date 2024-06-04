#ifndef GAME_H
#define GAME_H

#include "gui/SDL2Window.h"
#include "gui/assets.h"
#include "states/state_manager.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <memory>

/*
The name Game refers to the whole life of the window, namely Menus, Level
Selection, Game instance and so on
*/
class Game : public SDL2Window {
private:
  std::shared_ptr<Assets> assets_;
  GameStateManager *state_manager_;

  bool running_ = true;

public:
  Game(int screen_width, int screen_height);

  void run();

private:
  void drawLooseObjects();
  void drawWinObjects();
};

#endif
