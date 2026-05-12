#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Applies global physics forces to entities.
 */
class PhysicsSystem : public System {
  public:
    /**
     * @brief Constructor.
     */
    PhysicsSystem() {
      RequireComponent<RigidBodyComponent>();
    }

    /**
     * @brief Updates physics forces for all entities.
     */
    void Update() {
      for (auto entity : GetSystemEntities()) {
        auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

        // Aplicar fuerza de gravedad
        if (rigidbody.isDynamic) {
          rigidbody.sumForces += glm::vec2(0.0f, 9.8 * rigidbody.mass * 64);
        }
      }
    }
};

#endif  // PHYSICSSYSTEM_HPP