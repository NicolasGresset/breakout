#include "gui/menu.h"
#include "gui/levels.h"
#include "game.h"
#include "game_controller.h"
#include "utils/constants.h"

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  int code = 0;
  std::shared_ptr<SDL2Window> window = std::make_shared<SDL2Window>();//SDL2Window window{};

  bool quit_game = false;
  while (!quit_game)
  {
#ifndef GAME_TESTING
      Menu menu{window};
      code = menu.mainLoop();
#endif

      if (code == 1)
          return 0;
      if (code == 2)
      {
          Levels levels_interface{window};
          code = levels_interface.mainLoop();
          // Fermer
          if (code == -1)
              return 0;
          else
          {
              // Play a selected level
              if (code > 0)
              {
                  // The code correspond to a level
                  // The file path from the root of the project ./levels/level_{code}
                  GameController game_controller(window, WINDOW_WIDTH, WINDOW_HEIGHT, 3,
                                                 "./levels/level_" + std::to_string(code));
                  std::shared_ptr<Game> my_game = game_controller.getGame();

                  code = my_game->mainLoop();
                  if (code == 1)
                      quit_game = true;

              }
          }
      }
      else
      {
          GameController game_controller(window, WINDOW_WIDTH, WINDOW_HEIGHT, 3);
          std::shared_ptr<Game> my_game = game_controller.getGame();

          code = my_game->mainLoop();
          if (code == 1)
              quit_game = true;
      }
  }
  return 0;
}
