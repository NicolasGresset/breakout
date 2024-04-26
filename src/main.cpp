#include "game.h"
#include "game_controller.h"
#include "utils/constants.h"

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  GameController game_controller(WINDOW_HEIGHT, WINDOW_WIDTH, 3);
  std::shared_ptr<Game> my_game = game_controller.getGame();
  my_game->start();
  return 0;
}