#ifndef LIFETIMESYSTEM_HPP
#define LIFETIMESYSTEM_HPP

#include "../Components/LifetimeComponent.hpp"
#include "../ECS/ECS.hpp"

class LifetimeSystem : public System {
public:
    LifetimeSystem() {
        RequireComponent<LifetimeComponent>();
    }

    void Update(float dt) {
        for (auto entity : GetSystemEntities()) {
            auto& lifetime = entity.GetComponent<LifetimeComponent>();

            lifetime.remainingTime -= dt;

            if (lifetime.remainingTime <= 0.0f) {
                entity.Kill();
            }
        }
    }
};

#endif  // LIFETIMESYSTEM_HPP