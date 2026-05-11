#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

/**
 * @brief Defines the properties of the text of an entity.
 */
struct TextComponent {
  std::string text;
  std::string fontId;
  SDL_Color color;
  int width;
  int height;

  /**
   * @brief Constructor.
   *
   * @param text Text to display.
   * @param fontId Font.
   * @param r Part of color.
   * @param g Part of color.
   * @param b Part of color.
   * @param a Part of color.
   */
  TextComponent(const std::string& text = "", const std::string& fontId = ""
    , u_char r = 0, u_char g = 0, u_char b = 0, u_char a = 0) {
    this->text = text;
    this->fontId = fontId;
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
    this->width = 0;
    this->height = 0;
  }
};

#endif  // TEXTCOMPONENT_HPP