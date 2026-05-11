#ifndef LIFETIMECOMPONENT_HPP
#define LIFETIMECOMPONENT_HPP

/**
 * @brief Defines the lifetime of an entity that expires.
 */
struct LifetimeComponent {
  float remainingTime;

  /**
   * @brief Constructor.
   *
   * @param time Time until the entity expires.
   */
  LifetimeComponent(float time = 0.0f) {
    remainingTime = time;
  }
};

#endif  // LIFETIMECOMPONENT_HPP