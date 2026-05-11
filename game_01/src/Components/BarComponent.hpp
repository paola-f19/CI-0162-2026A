#ifndef BARCOMPONENT_HPP
#define BARCOMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @brief Types of UI resource bars.
 */
enum class BarType {
  HEALTH,
  SANITY
};

/**
 * @brief Defines the visual properties of a UI bar.
 */
struct BarComponent {
  int width;
  int height;

  int posX;
  int posY;

  SDL_Color fgColor;  // foreground color
  SDL_Color bgColor;  // background color

  BarType type;

  /**
   * @brief Constructor.
   *
   * @param width Width of bar.
   * @param height Height of bar.
   * @param posX Position x.
   * @param posY Position y.
   * @param fgColor Foreground color.
   * @param bgColor Background color.
   * @param type Type of bar.
   */
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