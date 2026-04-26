#ifndef PATROLCOMPONENT_HPP
#define PATROLCOMPONENT_HPP

#include <glm/glm.hpp>
#include <vector>

struct PatrolComponent {
  std::vector<glm::vec2> waypoints;
  int currentIndex;
  float speed;

  PatrolComponent(std::vector<glm::vec2> waypoints = {}
    , int currentIndex = 0, float speed = 0.0f) {
      this->waypoints = waypoints;
      this->currentIndex = currentIndex;
      this->speed = speed;
  }
};

#endif  // PATROLCOMPONENT_HPP