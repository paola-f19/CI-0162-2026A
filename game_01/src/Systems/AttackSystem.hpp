#ifndef ATTACKSYSTEM_HPP
#define ATTACKSYSTEM_HPP

#include <glm/glm.hpp>

#include <iostream>

#include "../Components/AttackComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/DamageComponent.hpp"
#include "../Components/DirectionComponent.hpp"
#include "../Components/FactionComponent.hpp"
#include "../Components/LifetimeComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"
#include "../Game/Game.hpp"

class AttackSystem : public System {
  private:
    void SpawnHitbox(Entity player, AttackComponent& attack) {
      std::cout << "[ATTACKSYSTEM] entered SpawnHitbox" << std::endl;

      auto& collider = player.GetComponent<BoxColliderComponent>();
      auto& transform = player.GetComponent<TransformComponent>();
      auto& faction = player.GetComponent<FactionComponent>();

      // Determine direction
      glm::vec2 direction = GetFacingDirection(player);

      // Offset forward
      glm::vec2 offset = direction * (attack.range * 0.5f);

      // Create hitbox entity
      Entity hitbox = Game::GetInstance().registry->CreateEntity();

      hitbox.AddComponent<TransformComponent>(
        glm::vec2(
          transform.position.x + offset.x,
          transform.position.y + offset.y
        ),
        transform.scale,
        transform.rotation
      );

      hitbox.AddComponent<BoxColliderComponent>(
        attack.range,
        attack.range,
        collider.offset
      );

      hitbox.AddComponent<DamageComponent>(attack.damage);

      hitbox.AddComponent<FactionComponent>(faction.faction);

      // Lifetime so it disappears automatically
      hitbox.AddComponent<LifetimeComponent>(attack.duration);
    }

    glm::vec2 GetFacingDirection(Entity player) {
      auto& dir = player.GetComponent<DirectionComponent>();
      return dir.direction;
    }

    void TriggerAnimation(Entity player) {
      std::cout << "[ATTACKSYSTEM] entered TriggerAnimation" << std::endl;
      auto& script = player.GetComponent<ScriptComponent>();
      script.startAttack();
    }

  
  public:
    AttackSystem() {
      RequireComponent<AttackComponent>();
      RequireComponent<BoxColliderComponent>();
      RequireComponent<DirectionComponent>();
      RequireComponent<FactionComponent>();
      RequireComponent<ScriptComponent>();
      RequireComponent<TransformComponent>();
    }

    void SubscribeToClickEvent(const std::unique_ptr<EventManager>& eventManager) {
      eventManager->SubscribeToEvent<ClickEvent, AttackSystem>(
        this, &AttackSystem::OnClickEvent);
    }
    
    void OnClickEvent(ClickEvent& e) {
      // attack only on left click
      if (e.buttonCode != 1) return;

      for (auto entity : GetSystemEntities()) {

        auto& attack = entity.GetComponent<AttackComponent>();

        if (attack.cooldownRemaining > 0.0f) return;

        attack.isAttacking = true;
        attack.timeRemaining = attack.duration;
        attack.cooldownRemaining = attack.cooldown;

        // attack hitbox
        SpawnHitbox(entity, attack);

        // attack animation
        TriggerAnimation(entity);
      }
    }

    // handle timings
    void Update(float deltaTime) {
      for (auto entity : GetSystemEntities()) {
        auto& attack = entity.GetComponent<AttackComponent>();

        if (attack.cooldownRemaining > 0.0f) {
          attack.cooldownRemaining -= deltaTime;
        }

        if (attack.isAttacking) {
          attack.timeRemaining -= deltaTime;

          if (attack.timeRemaining <= 0.0f) {
            attack.isAttacking = false;
          }
        }
      }
    }

};

#endif  // ATTACKSYSTEM_HPP