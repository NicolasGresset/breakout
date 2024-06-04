#include "game.h"
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

  Game game(WINDOW_WIDTH, WINDOW_HEIGHT);
  game.run();
  return 0;
}
