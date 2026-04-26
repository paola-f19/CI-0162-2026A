#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

#include <SDL2/SDL.h>

struct HealthBarComponent {
    int width;
    int height;
    SDL_Color fgColor;  // health color
    SDL_Color bgColor;  // background color

    HealthBarComponent(int width = 0, int height = 0
      , SDL_Color fgColor = {0, 0, 0, 0}, SDL_Color bgColor = {0, 0, 0, 0}) {
        this->width = width;
        this->height = height;
        this->fgColor = fgColor;
        this->bgColor = bgColor;
      }
};

#endif  // HEALTHBARCOMPONENT_HPP