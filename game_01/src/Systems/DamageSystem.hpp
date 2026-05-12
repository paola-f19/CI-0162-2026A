#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>  // TODO: eliminar mas adelante
#include <memory>

#include "../Components/DamageComponent.hpp"
#include "../Components/FactionComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../Game/Game.hpp"

/**
 * @brief Applies damage to entities during collisions.
 */
class DamageSystem : public System {
  private:
    /**
     * @brief Applies damage from one entity to another.
     *
     * @param a Entity receiving damage.
     * @param b Entity dealing damage.
     */
    void HandleDamage(Entity a, Entity b) {
      if (!a.HasComponent<HealthComponent>()) return;
      if (!b.HasComponent<DamageComponent>()) return;

      if (a.HasComponent<FactionComponent>() && b.HasComponent<FactionComponent>()) {
        auto aFaction = a.GetComponent<FactionComponent>().faction;
        auto bFaction = b.GetComponent<FactionComponent>().faction;

        if (aFaction == bFaction) return;
      }

      auto& health = a.GetComponent<HealthComponent>();
      const auto& damage = b.GetComponent<DamageComponent>();

      // invulnerability check
      if (health.invulnerableTime > 0.0f) return;

      health.currentHealth -= damage.damage;

      // sound effect
      // TODO: only for player? diff sound for others?
      Game::GetInstance().audioManager->PlaySound("hurt");

      std::cout << "[DAMAGESYSTEM] " << damage.damage << " damage taken" << std::endl;
      health.invulnerableTime = 0.5f;

      if (health.currentHealth <= 0) {
        std::cout << "[DAMAGESYSTEM] Entity has died" << std::endl;
        a.Kill();
      }
    }

  public:
    /**
     * @brief Constructor.
     */
    DamageSystem() {
      RequireComponent<HealthComponent>();
    }

    /**
     * @brief Subscribes the system to collision events.
     *
     * @param eventManager Event manager handling subscriptions.
     */
    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
      eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this
        , &DamageSystem::OnCollision);
    }

    /**
     * @brief Handles collision events and applies damage.
     *
     * @param e Collision event data.
     */
    void OnCollision(CollisionEvent& e) {
      HandleDamage(e.a, e.b);
      HandleDamage(e.b, e.a);
    }
};

#endif  // DAMAGESYSTEM_HPP