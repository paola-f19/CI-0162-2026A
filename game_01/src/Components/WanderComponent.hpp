#ifndef WANDERCOMPONENT_HPP
#define WANDERCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Defines a movement pattern where the entity wanders randomly within 
 *        a defined radius.
 */
struct WanderComponent {
  glm::vec2 origin;
  float radius;
  glm::vec2 target = glm::vec2(0);
  float speed;

  /**
   * @brief Constructor.
   *
   * @param origin Origin of the wander circle.
   * @param radius Radius of wander circle.
   * @param speed Movement speed.
   */
  WanderComponent(glm::vec2 origin = glm::vec2(0), float radius = 0.0f
    , float speed = 0.0f) {
    this->origin = origin;
    this->radius = radius;
    this->speed = speed;
  }
};

#endif  // WANDERCOMPONENT_HPP