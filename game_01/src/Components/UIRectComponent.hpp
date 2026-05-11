#ifndef UIRECTCOMPONENT_HPP
#define UIRECTCOMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @brief Defines an entity that is an UI rectangle.
 */
struct UIRectComponent {
  int width;
  int height;
  SDL_Color color;
  
  /**
   * @brief Constructor.
   *
   * @param width Width of rectangle.
   * @param height Height of rectangle.
   * @param color Color of rectangle.
   */
  UIRectComponent(int width = 0, int height = 0
    , SDL_Color color = {0, 0, 0, 0}) {
    this->width = width;
    this->height = height;
    this->color = color;
  }
};

#endif  // UIRECTCOMPONENT_HPP