#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
    sol::function onCollision;
    sol::function onClick;
    sol::function update;

    ScriptComponent(sol::function onCollision = sol::lua_nil
        , sol::function onClick = sol::lua_nil
        , sol::function update = sol::lua_nil) {
        this->onCollision = onCollision;
        this->onClick = onClick;
        this->update = update;
    }
};

#endif  // SCRIPTCOMPONENT_HPP