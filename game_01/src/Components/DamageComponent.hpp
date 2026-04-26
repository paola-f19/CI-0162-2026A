#ifndef DAMAGECOMPONENT_HPP
#define DAMAGECOMPONENT_HPP

struct DamageComponent {
  int damage;

  DamageComponent(int damage = 0) {
    this->damage = damage;
  }
};

#endif  // DAMAGECOMPONENT_HPP