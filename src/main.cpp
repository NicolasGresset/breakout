#include "game.h"

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  Game my_game;
  my_game.init();
  // my_game.foo();
  my_game.mainLoop();
  return 0;
}