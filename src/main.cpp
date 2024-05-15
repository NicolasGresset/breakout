#include "gui/menu.h"
#include "gui/levels.h"
#include "game.h"
#include "game_controller.h"
#include "utils/constants.h"

/**
 * The project has multiple interfaces. The interfaces are the game
 interface and interfaces with multiple buttons to choose actions.
 The game interface has a dock for the player. It is a considered as a
 rectangle and a movable object. It can be controlled with the arrow
 keys. The ball (considered also as a movable object) can bounce on
 it.  The bricks are rectangles aligned in a grid. They can have
 different lives. When the ball bounce on a brick it decrement the
 lives of this brick and destroy it if it has no more lives. Finally,
 when a brick is destroyed a bonus appears. There are 3 types of
 bonuse : obtain an extra life, increase the ball speed and create
 more balls.


 * The interfaces with buttons allows the player to choose different
 actions. Those interfaces are for the menu to choose to play, to quit
 or to choose a level, the level interface and the pause interface
 that shows the current score.
*/

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
