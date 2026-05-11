#ifndef PATROLCOMPONENT_HPP
#define PATROLCOMPONENT_HPP

#include <glm/glm.hpp>
#include <vector>

/**
 * @brief Defines a movement pattern where the entity follows a set of 
 *        coordinates.
 */
struct PatrolComponent {
  std::vector<glm::vec2> waypoints;
  int currentIndex;
  float speed;

  /**
   * @brief Constructor.
   *
   * @param waypoints Vector of coordinates.
   * @param currentIndex Current index in waypoints to go after.
   * @param speed Movement speed.
   */
  PatrolComponent(std::vector<glm::vec2> waypoints = {}
    , int currentIndex = 0, float speed = 0.0f) {
    this->waypoints = waypoints;
    this->currentIndex = currentIndex;
    this->speed = speed;
  }
};

#endif  // PATROLCOMPONENT_HPP