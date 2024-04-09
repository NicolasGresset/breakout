#include "../include/game.h"

int main(int argc, char *argv[]) {
  Game my_game;
  my_game.init();
  // my_game.foo();
  my_game.mainLoop();
  return 0;
}