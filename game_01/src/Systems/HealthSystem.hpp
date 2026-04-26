#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"

class HealthSystem : public System {
  public:
    HealthSystem() {
      RequireComponent<HealthComponent>();
    }

    void Update(float deltaTime) {
      for (auto entity : GetSystemEntities()) {
        auto& health = entity.GetComponent<HealthComponent>();

        if (health.invulnerableTime > 0.0f) {
          health.invulnerableTime -= deltaTime;

          if (health.invulnerableTime < 0.0f) {
            health.invulnerableTime = 0.0f;
          }
        }
      }
    }
};

#endif  // HEALTHSYSTEM_HPP