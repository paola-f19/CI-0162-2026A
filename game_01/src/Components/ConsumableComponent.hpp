#ifndef CONSUMABLECOMPONENT_HPP
#define CONSUMABLECOMPONENT_HPP

enum class ConsumableType {
  HEALTH,
  SANITY
};

struct ConsumableComponent {
  ConsumableType type;
  int amount;

  ConsumableComponent(ConsumableType type = ConsumableType::HEALTH
    , int amount = 0) {
    this->type = type;
    this->amount = amount;
  }
};

#endif  // CONSUMABLECOMPONENT_HPP