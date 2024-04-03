#include "../include/SDL2Window.h"

int main(int argc, char *argv[]) {
  SDL2Window window;
  window.init();
  window.drawCirle(300, 300, 200);
  window.update();
  window.temporisation(4000);
  return 0;
}