#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>  // TODO: eliminar mas adelante
#include <memory>

#include "../Components/DamageComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {
    private:
        void HandleDamage(Entity a, Entity b) {
            if (!a.HasComponent<HealthComponent>()) return;
            if (!b.HasComponent<DamageComponent>()) return;

            auto& health = a.GetComponent<HealthComponent>();
            const auto& damage = b.GetComponent<DamageComponent>();

            // invulnerability check
            if (health.invulnerableTime > 0.0f) return;

            health.currentHealth -= damage.damage;
            std::cout << "[DAMAGESYSTEM] " << damage.damage << " damage taken" << std::endl;
            health.invulnerableTime = 0.5f;

            if (health.currentHealth <= 0) {
                std::cout << "[DAMAGESYSTEM] Entity has died" << std::endl;
                a.Kill();
            }
        }

    public:
        DamageSystem() {
            RequireComponent<HealthComponent>();
        }

        void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this
                , &DamageSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& e) {
            // TODO: both do damage to each other, fix
            HandleDamage(e.a, e.b);
            HandleDamage(e.b, e.a);
        }
};

#endif  // DAMAGESYSTEM_HPP