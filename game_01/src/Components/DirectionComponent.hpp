#ifndef DIRECTIONCOMPONENT_HPP
#define DIRECTIONCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Defines the direction an entity faces.
 */
struct DirectionComponent {
  glm::vec2 direction;

  /**
   * @brief Constructor.
   *
   * @param direction Current facing direction of an entity.
   */
  DirectionComponent(glm::vec2 direction = glm::vec2(0, 1)) {
    this->direction = direction;
  }
};

#endif  // DIRECTIONCOMPONENT_HPP