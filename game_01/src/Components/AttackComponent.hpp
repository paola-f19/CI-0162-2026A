#ifndef ATTACKCOMPONENT_HPP
#define ATTACKCOMPONENT_HPP

/**
 * @brief Stores the information of an attack.
 */
struct AttackComponent {
  int damage;
  float range;   // how far the attack reaches
  float duration;  // how long the hitbox exists
  float cooldown;

  float timeRemaining = 0.0f;
  float cooldownRemaining = 0.0f;

  bool isAttacking = false;

  /**
   * @brief Constructor.
   *
   * @param damage Damage of atack.
   * @param range Range of attack.
   * @param duration Duration of attack.
   * @param cooldown Cooldown of attack.
   */
  AttackComponent(int damage = 0, float range = 0.0f, float duration = 0.0f
    , float cooldown = 0.0f) {
    this->damage = damage;
    this->range = range;
    this->duration = duration;
    this->cooldown = cooldown;
  }
};

#endif  // ATTACKCOMPONENT_HPP