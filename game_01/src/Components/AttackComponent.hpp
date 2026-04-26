#ifndef ATTACKCOMPONENT_HPP
#define ATTACKCOMPONENT_HPP

struct AttackComponent {
  int damage;
  float range;   // how far the attack reaches
  float duration;  // how long the hitbox exists
  float cooldown;

  float timeRemaining = 0.0f;
  float cooldownRemaining = 0.0f;

  bool isAttacking = false;

  AttackComponent(int damage = 0, float range = 0.0f, float duration = 0.0f
    , float cooldown = 0.0f) {
    this->damage = damage;
    this->range = range;
    this->duration = duration;
    this->cooldown = cooldown;
  }
};

#endif  // ATTACKCOMPONENT_HPP