#ifndef UIRECTCOMPONENT_HPP
#define UIRECTCOMPONENT_HPP

#include <SDL2/SDL.h>

struct UIRectComponent {
    int width;
    int height;
    SDL_Color color;

    UIRectComponent(int width = 0, int height = 0
      , SDL_Color color = {0, 0, 0, 0}) {
      this->width = width;
      this->height = height;
      this->color = color;
    }
};

#endif  // UIRECTCOMPONENT_HPP