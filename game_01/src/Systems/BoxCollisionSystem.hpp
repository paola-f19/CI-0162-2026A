#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/ConsumableComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SanityComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @brief Detects and handles box collisions between entities.
 */
class BoxCollisionSystem : public System {
  private:
    /**
     * @brief Checks collision between two axis-aligned bounding boxes.
     *
     * @param aX First box X position.
     * @param aY First box Y position.
     * @param aW First box width.
     * @param aH First box height.
     * @param bX Second box X position.
     * @param bY Second box Y position.
     * @param bW Second box width.
     * @param bH Second box height.
     *
     * @return True if the boxes overlap.
     */
    bool CheckAABBCollision(float aX, float aY, float aW, float aH, float bX
      , float bY, float bW, float bH) {
      return(
        aX < bX + bW &&
        aX + aW > bX &&
        aY < bY + bH &&
        aY + aH > bY
      );
    }

    /**
     * @brief Applies consumable effects to the player.
     *
     * @param player Player entity receiving the effect.
     * @param potion Consumable entity being collected.
     */
    void HandleConsumablePickup(Entity player, Entity potion) {

      auto& consumable = potion.GetComponent<ConsumableComponent>();

      // HEALTH
      if (consumable.type == ConsumableType::HEALTH &&
        player.HasComponent<HealthComponent>()) {
        auto& health = player.GetComponent<HealthComponent>();

        health.currentHealth += consumable.amount;
        health.currentHealth = std::min(
          health.currentHealth,
          health.maxHealth
        );
      }
      // SANITY
      else if (consumable.type == ConsumableType::SANITY &&
        player.HasComponent<SanityComponent>()) {
        auto& sanity = player.GetComponent<SanityComponent>();
        std::cout << "Current sanity: " << sanity.currentSanity << std::endl;

        sanity.currentSanity += consumable.amount;
        std::cout << "Sanity after adding: " << sanity.currentSanity << std::endl;
        std::cout << "Max sanity:  " << sanity.maxSanity << std::endl;
        sanity.currentSanity = std::min(
          sanity.currentSanity,
          sanity.maxSanity
        );
        std::cout << consumable.amount << " Sanity gained !" << std::endl;
        std::cout << "Sanity now: " << sanity.currentSanity << std::endl;
      }

      // Destroy potion
      potion.Kill();
    }

  public:
    /**
     * @brief Constructor.
     */
    BoxCollisionSystem() {
      RequireComponent<BoxColliderComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Updates collision detection and collision responses.
     *
     * @param eventManager Event manager used for collision events.
     * @param lua Lua state used for scripted callbacks.
     */
    void Update(const std::unique_ptr<EventManager>& eventManager
      , sol::state& lua) {
      auto entities = GetSystemEntities();

      for (auto i = entities.begin(); i != entities.end(); i++) {
        Entity a = *i;
        const auto& aCollider = a.GetComponent<BoxColliderComponent>();
        const auto& aTransform = a.GetComponent<TransformComponent>();

        for (auto j = i; j != entities.end(); j++) {
          Entity b = *j;

          if (a == b) {
            continue;
          }

          const auto& bCollider = b.GetComponent<BoxColliderComponent>();
          const auto& bTransform = b.GetComponent<TransformComponent>();

          bool collision = CheckAABBCollision(
            aTransform.position.x + aCollider.offset.x,
            aTransform.position.y + aCollider.offset.y,
            static_cast<float>(aCollider.width),
            static_cast<float>(aCollider.height),
            bTransform.position.x + bCollider.offset.x,
            bTransform.position.y + bCollider.offset.y,
            static_cast<float>(bCollider.width),
            static_cast<float>(bCollider.height)
          );

          if (collision) {
            eventManager->EmitEvent<CollisionEvent>(a, b);

            if (a.HasComponent<RigidBodyComponent>()) {
                a.GetComponent<RigidBodyComponent>().collided = true;
            }

            if (b.HasComponent<RigidBodyComponent>()) {
                b.GetComponent<RigidBodyComponent>().collided = true;
            }

            if (a.HasComponent<ScriptComponent>()) {
              const auto& script = a.GetComponent<ScriptComponent>();
              if (script.onCollision != sol::nil) {
                lua["this"] = a;
                script.onCollision(b);
              }
            }
            
            if (b.HasComponent<ScriptComponent>()) {
              const auto& script = b.GetComponent<ScriptComponent>();
              if (script.onCollision != sol::nil) {
                lua["this"] = b;
                script.onCollision(a);
              }
            }
            
            // Consumable pickup 
            if (a.HasComponent<TagComponent>() &&
              b.HasComponent<ConsumableComponent>())
            {
              const auto& tag = a.GetComponent<TagComponent>();
              if (tag.tag == "player") {
                HandleConsumablePickup(a, b);
              }
            }

            if (b.HasComponent<TagComponent>() &&
              a.HasComponent<ConsumableComponent>())
            {
              const auto& tag = b.GetComponent<TagComponent>();
              if (tag.tag == "player") {
                HandleConsumablePickup(b, a);
              }
            }
          }
        }
      }
    }
};

#endif  // BOXCOLLISIONSYSTEM_HPP