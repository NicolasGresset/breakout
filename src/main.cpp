#include "game.h"

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  Game my_game;
  my_game.init();

  // my_game.foo();
 #ifndef GAME_TESTING
  my_game.menuMainLoop();
#endif
  my_game.gameMainLoop();
  return 0;
}
