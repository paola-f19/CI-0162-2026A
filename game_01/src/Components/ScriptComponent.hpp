#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
    sol::function onCollision;
    sol::function onClick;
    sol::function update;
    sol::function startAttack;

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