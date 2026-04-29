#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP

#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class BoxCollisionSystem : public System {
  private:
    bool CheckAABBCollision(float aX, float aY, float aW, float aH, float bX
      , float bY, float bW, float bH) {
      return(
        aX < bX + bW &&
        aX + aW > bX &&
        aY < bY + bH &&
        aY + aH > bY
      );
    }

  public:
    BoxCollisionSystem() {
      RequireComponent<BoxColliderComponent>();
      RequireComponent<TransformComponent>();
    }

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
          }
        }
      }
    }
};

#endif  // BOXCOLLISIONSYSTEM_HPP