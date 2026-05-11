#ifndef DAMAGECOMPONENT_HPP
#define DAMAGECOMPONENT_HPP


/**
 * @brief Describes damage.
 */
struct DamageComponent {
  int damage;

  /**
   * @brief Constructor.
   *
   * @param damage Value of damage.
   */
  DamageComponent(int damage = 0) {
    this->damage = damage;
  }
};

#endif  // DAMAGECOMPONENT_HPP