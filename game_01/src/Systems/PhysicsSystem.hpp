#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

class PhysicsSystem : public System {
    public:
        PhysicsSystem() {
            RequireComponent<RigidBodyComponent>();
        }

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