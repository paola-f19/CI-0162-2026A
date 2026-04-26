#ifndef FACTIONCOMPONENT_HPP
#define FACTIONCOMPONENT_HPP

#include <string>

struct FactionComponent {
    std::string faction;

    FactionComponent(const std::string& faction = "")  {
        this->faction = faction;
    }
};

#endif  // FACTIONCOMPONENT_HPP