#include "game.h"
#include "game_controller.h"
#include "utils/constants.h"

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  GameController game_controller(WINDOW_WIDTH, WINDOW_HEIGHT, 3);
  std::shared_ptr<Game> my_game = game_controller.getGame();
  my_game->start();

 #ifndef GAME_TESTING
  my_game->menuMainLoop();
 #endif
  my_game->gameMainLoop();
  return 0;
}
