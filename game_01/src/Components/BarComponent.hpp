#ifndef BARCOMPONENT_HPP
#define BARCOMPONENT_HPP

#include <SDL2/SDL.h>

enum class BarType {
  HEALTH,
  SANITY
};

struct BarComponent {
    int width;
    int height;

    int posX;
    int posY;

    SDL_Color fgColor;  // foreground color
    SDL_Color bgColor;  // background color

    BarType type;

    BarComponent(int width = 0, int height = 0, int posX = 0, int posY = 0
      , SDL_Color fgColor = {0, 0, 0, 0}, SDL_Color bgColor = {0, 0, 0, 0}
      , BarType type = BarType::HEALTH) {
        this->width = width;
        this->height = height;
        this->posX = posX;
        this->posY = posY;
        this->fgColor = fgColor;
        this->bgColor = bgColor;
        this->type = type;
      }
};

#endif  // BARCOMPONENT_HPP