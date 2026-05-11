#ifndef BOXCOLLIDERCOMPONENT_HPP
#define BOXCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Defines the properties of a box collider.
 */
struct BoxColliderComponent {
  int width;
  int height;
  glm::vec2 offset;

  /**
   * @brief Constructor.
   *
   * @param width Width of collider.
   * @param height Height of collider.
   * @param offset Offset.
   */
  BoxColliderComponent(int width = 0, int height = 0
    , glm::vec2 offset = glm::vec2(0)) {
    this->width = width;
    this->height = height;
    this->offset = offset;
  }
};

#endif  // BOXCOLLIDERCOMPONENT_HPP