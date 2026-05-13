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
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"
#include "../Game/Game.hpp"

/**
 * @brief Handles melee attacks and attack hitboxes.
 */
class AttackSystem : public System {
  private:
    /**
     * @brief Creates a temporary attack hitbox entity.
     *
     * @param player Attacking entity.
     * @param attack Attack configuration data.
     */
    void SpawnHitbox(Entity player, AttackComponent& attack) {
      std::cout << "[ATTACKSYSTEM] entered SpawnHitbox" << std::endl;

      // auto& collider = player.GetComponent<BoxColliderComponent>();
      auto& sprite = player.GetComponent<SpriteComponent>();
      auto& transform = player.GetComponent<TransformComponent>();
      auto& faction = player.GetComponent<FactionComponent>();

      // Determine direction
      glm::vec2 direction = GetFacingDirection(player);

      std::cout << "[ATTACKSYSTEM] direction position ( " << direction.x << ", " << direction.y << " )" << std::endl;

      glm::vec2 playerCenter =
        transform.position +
        sprite.offset +
      glm::vec2(
        sprite.width * 0.5f,
        sprite.height * 0.5f
      );

      // Distance from player center to hitbox center
      float attackDistance = 16.0f;

      // Hitbox center
      glm::vec2 hitboxCenter =
        playerCenter +
        direction * attackDistance;

      // Convert center -> top-left
      glm::vec2 hitboxPosition =
        hitboxCenter -
        glm::vec2(
          attack.range * 0.5f,
          attack.range * 0.5f
        );

      // Create hitbox entity
      Entity hitbox = Game::GetInstance().registry->CreateEntity();

      std::cout << "[ATTACKSYSTEM] transform position ( " << transform.position.x << ", " << transform.position.y << " )" << std::endl;

      hitbox.AddComponent<TransformComponent>(
        hitboxPosition,
        glm::vec2(1.0f, 1.0f),
        0.0f
      );

      hitbox.AddComponent<BoxColliderComponent>(
        attack.range * 2,
        attack.range * 2,
        glm::vec2(0.0f, 0.0f)
      );

      hitbox.AddComponent<DamageComponent>(attack.damage);

      hitbox.AddComponent<FactionComponent>(faction.faction);

      // Lifetime so it disappears automatically
      hitbox.AddComponent<LifetimeComponent>(attack.duration);
    }

    /**
     * @brief Retrieves the facing direction of an entity.
     *
     * @param player Entity whose direction is requested.
     * @return Normalized direction vector.
     */
    glm::vec2 GetFacingDirection(Entity player) {
      auto& dir = player.GetComponent<DirectionComponent>();
      return dir.direction;
    }

    /**
     * @brief Triggers the attack animation of an entity.
     *
     * @param player Attacking entity.
     */
    void TriggerAnimation(Entity player) {
      std::cout << "[ATTACKSYSTEM] entered TriggerAnimation" << std::endl;
      auto& script = player.GetComponent<ScriptComponent>();
      script.startAttack();
    }

  public:
    /**
     * @brief Constructor.
     */
    AttackSystem() {
      RequireComponent<AttackComponent>();
      RequireComponent<BoxColliderComponent>();
      RequireComponent<DirectionComponent>();
      RequireComponent<FactionComponent>();
      RequireComponent<ScriptComponent>();
      RequireComponent<SpriteComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Subscribes the system to click events.
     *
     * @param eventManager Event manager handling subscriptions.
     */
    void SubscribeToClickEvent(const std::unique_ptr<EventManager>& eventManager) {
      eventManager->SubscribeToEvent<ClickEvent, AttackSystem>(
        this, &AttackSystem::OnClickEvent);
    }
    
    /**
     * @brief Handles mouse click attack input.
     *
     * @param e Click event data.
     */
    void OnClickEvent(ClickEvent& e) {
      // attack only on left click
      if (e.buttonCode != 1) return;

      for (auto entity : GetSystemEntities()) {

        auto& attack = entity.GetComponent<AttackComponent>();

        if (attack.cooldownRemaining > 0.0f) return;

        attack.isAttacking = true;
        attack.timeRemaining = attack.duration;
        attack.cooldownRemaining = attack.cooldown;

        // sound effect
        Game::GetInstance().audioManager->PlaySound("slash");

        // attack hitbox
        SpawnHitbox(entity, attack);

        // attack animation
        TriggerAnimation(entity);
      }
    }

    /**
     * @brief Updates attack timers and cooldowns.
     *
     * @param deltaTime Time elapsed since the previous frame.
     */
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