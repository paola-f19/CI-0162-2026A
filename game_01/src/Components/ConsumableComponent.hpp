#ifndef CONSUMABLECOMPONENT_HPP
#define CONSUMABLECOMPONENT_HPP

/**
 * @brief Types of consumables.
 */
enum class ConsumableType {
  HEALTH,
  SANITY
};

/**
 * @brief Defines the properties of a consumable.
 */
struct ConsumableComponent {
  ConsumableType type;
  int amount;

  /**
   * @brief Constructor.
   *
   * @param type Type of consumable.
   * @param amount Value of health/sanity to restore.
   */
  ConsumableComponent(ConsumableType type = ConsumableType::HEALTH
    , int amount = 0) {
    this->type = type;
    this->amount = amount;
  }
};

#endif  // CONSUMABLECOMPONENT_HPP