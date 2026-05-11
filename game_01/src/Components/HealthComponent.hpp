#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

/**
 * @brief Defines the health of an entity.
 */
struct HealthComponent {
  int maxHealth;
  int currentHealth;
  float invulnerableTime = 0.0f;

  /**
   * @brief Constructor.
   *
   * @param maxHealth Maximum health.
   * @param currentHealth Current health.
   */
  HealthComponent(int maxHealth = 0, int currentHealth = 0) {
    this->maxHealth = maxHealth;
    this->currentHealth = currentHealth;
  }
};

#endif  // HEALTHCOMPONENT_HPP