#ifndef LIFETIMESYSTEM_HPP
#define LIFETIMESYSTEM_HPP

#include "../Components/LifetimeComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Removes entities after a timed duration.
 */
class LifetimeSystem : public System {
  public:
    /**
     * @brief Constructor.
     */
    LifetimeSystem() {
      RequireComponent<LifetimeComponent>();
    }

    /**
     * @brief Updates entity lifetimes.
     *
     * @param dt Frame delta time in seconds.
     */
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