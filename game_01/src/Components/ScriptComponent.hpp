#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @brief Defines the scripted behaviors of an entity.
 */
struct ScriptComponent {
  sol::function onCollision;
  sol::function onClick;
  sol::function update;
  sol::function startAttack;

  /**
   * @brief Constructor.
   *
   * @param onCollision Function to execute on collision event.
   * @param onClick Function to execute on click event.
   * @param update Update function.
   * @param startAttack Function to initiate an attack.
   */
  ScriptComponent(sol::function onCollision = sol::lua_nil
    , sol::function onClick = sol::lua_nil
    , sol::function update = sol::lua_nil
    , sol::function startAttack = sol::lua_nil) {
    this->onCollision = onCollision;
    this->onClick = onClick;
    this->update = update;
    this->startAttack = startAttack;
  }
};

#endif  // SCRIPTCOMPONENT_HPP