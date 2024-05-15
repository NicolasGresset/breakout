# Breakout

## Description

The project is the implementation of a brick-breaker. It includes a
graphical menu interface that lets you play, choose your
level. The game interface is standard to the original brick-breaker, with
a platform and a ball that can bounce between them to
destroy the (rectangular) bricks. These bricks can have
have several lives and a different configuration depending on the
levels.

## Features Description

The project has multiple interfaces. The interfaces are the game
interface and interfaces with multiple buttons to choose actions.  The
game interface has a dock for the player. It is a considered as a
rectangle and a movable object. It can be controlled with the arrow
keys. The ball (considered also as a movable object) can bounce on it.
The bricks are rectangles aligned in a grid. They can have different
lives. When the ball bounce on a brick it decrement the lives of this
brick and destroy it if it has no more lives. Finally, when a brick is
destroyed a bonus appears. There are 3 types of bonuse : obtain an
extra life, increase the ball speed and create more balls.


The interfaces with buttons allows the player to choose different
actions. Those interfaces are for the menu to choose to play, to quit
or to choose a level, the level interface and the pause interface that
shows the current score.

## Usage

To compile the game, the script `build.sh` can be used. It will used
the file `CMakeLists.txt` where all the dependencies are.

At the end of the compilation, the binary is in the folder `build`. To
launch the binary, the command `./build/main` is needed.


## Treeview of the project

    .
    ├── build
    ├── docs
    │   ├── html
    │   │   └── search
    │   └── latex
    ├── include
    |__ |__
    │   ├── object
    │   │__
    │   | gui
    |__ |__
    │   ├── utils
    |__ |__
    │   ├── bonus
    │   │
    │   └── gui
    ├── obj
    ├──
    ├── textures
    └── src
        |__
        |── object
        │__
        | gui
        ├── utils
        |__
        ├── bonus
        │
        └── gui


`.cpp` files are in the `src/` folder and headers file `.h` are in the
`include/` folder. However, subfolders exist to organize the tree. For
example, all classes that inherate the object class are in the sub
folder objects : ball, rectangle, rectangle_brick and dock.

## Coding Convention

You will use the following coding convention:
- `NomDeClasse`
- `nomDeFonction`.
- `var_name`
- `member_table_name_`
- use `{}` for calling constructors instead of `()`
- initialization list
- use `heightOfStackedBox(int nBoxes, float singleBoxHeight)` instead of `heightOfStackedBox(int, float)`
- function of less than two lines should be inline


## Language

- as much as possible, use english to name variables or commentaries to be consistent
