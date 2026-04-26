#ifndef DIRECTIONCOMPONENT_HPP
#define DIRECTIONCOMPONENT_HPP

#include <glm/glm.hpp>

struct DirectionComponent {
  glm::vec2 direction;

  DirectionComponent(glm::vec2 direction = glm::vec2(0, 1)) {
    this->direction = direction;
  }
};

#endif  // DIRECTIONCOMPONENT_HPP