#ifndef FOLLOWCOMPONENT_HPP
#define FOLLOWCOMPONENT_HPP

/**
 * @brief Defines a movement pattern where the entity follows the player.
 */
struct FollowComponent {
  float speed;
  float detectionRadius;

  /**
   * @brief Constructor.
   *
   * @param speed Movement speed.
   * @param detectionRadius Radius wherein the entity will follow.
   */
  FollowComponent(float speed = 0.0f, float detectionRadius = 0.0f) {
    this->speed = speed;
    this->detectionRadius = detectionRadius;
  }
};

#endif  // FOLLOWCOMPONENT_HPP