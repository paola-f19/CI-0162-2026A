#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include <string>

/**
 * @brief Defines the properties of the sprite of an entity.
 */
struct SpriteComponent {
  std::string textureId;
  int width;
  int height;
  SDL_Rect srcRect;
  glm::vec2 offset;
  bool flip = false;

  /**
   * @brief Constructor.
   *
   * @param textureId Id of the texture.
   * @param width Width of sprite.
   * @param height Height of sprite.
   * @param srcRectX Source rectangle x.
   * @param srcRectY Source rectangle y.
   * @param offset Offset of image.
   */
  SpriteComponent(const std::string& textureId = "none", int width = 0
    , int height = 0, int srcRectX = 0, int srcRectY = 0
    , glm::vec2 offset = glm::vec2(0)) {
    this->textureId = textureId,
    this->width = width;
    this->height = height;
    this->srcRect = {srcRectX, srcRectY, width, height};
    this->offset = offset;
  }
};

#endif  // SPRITECOMPONENT_HPP