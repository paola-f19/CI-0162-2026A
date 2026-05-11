#ifndef FACTIONCOMPONENT_HPP
#define FACTIONCOMPONENT_HPP

#include <string>

/**
 * @brief Defines the faction an entity belongs to.
 */
struct FactionComponent {
  std::string faction;

  /**
   * @brief Constructor.
   *
   * @param faction Faction of the entity.
   */
  FactionComponent(const std::string& faction = "")  {
    this->faction = faction;
  }
};

#endif  // FACTIONCOMPONENT_HPP