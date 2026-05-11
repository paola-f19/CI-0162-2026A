#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Defines the transform properties of an entity.
 */
struct TransformComponent {
  glm::vec2 position;
  glm::vec2 previousPosition;
  glm::vec2 scale;
  double rotation;

  /**
   * @brief Constructor.
   *
   * @param position Position coordinates.
   * @param scale Scale of entity.
   * @param rotation Rotation of entity.
   */
  TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0)
    , glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0) {
    this->position = position;
    this->previousPosition = position;
    this->scale = scale;
    this->rotation = rotation;
  }
};

#endif  // TRANSFORMCOMPONENT_HPP