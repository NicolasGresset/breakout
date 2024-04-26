#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game.h"
#include <memory>

class GameController {
private:
  std::shared_ptr<Game> game_;

  void init(int screen_width, int screen_height, int life);
public:
  GameController();
  GameController(int screen_width, int screen_height, int life) {
    init(screen_width, screen_height, life);
  };


  inline std::shared_ptr<Game> getGame() { return game_; }
};

#endif