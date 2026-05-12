#ifndef CIRCLECOLLISIONSYSTEM_HPP
#define CIRCLECOLLISIONSYSTEM_HPP

#include <memory>

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @brief Detects circular collisions between entities.
 */
class CircleCollisionSystem : public System {
  public:
    /**
     * @brief Constructor.
     */
    CircleCollisionSystem() {
      RequireComponent<CircleColliderComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Updates collision detection for all circular colliders.
     *
     * @param eventManager Event manager used to emit collision events.
     */
    void Update(std::unique_ptr<EventManager>& eventManager) {
      auto entities = GetSystemEntities();

      for (auto i = entities.begin(); i != entities.end(); i++) {
        Entity a = *i;
        auto aCollider = a.GetComponent<CircleColliderComponent>();
        auto aTransform = a.GetComponent<TransformComponent>();

        for (auto j = i; j != entities.end(); j++) {
          Entity b = *j;

          if (a == b) {
            continue;
          }

          auto bCollider = b.GetComponent<CircleColliderComponent>();
          auto bTransform = b.GetComponent<TransformComponent>();

          glm::vec2 aCenterPos = glm::vec2(
            aTransform.position.x - (aCollider.width / 2) * aTransform.scale.x,
            aTransform.position.y - (aCollider.height / 2) * aTransform.scale.y
          );

          glm::vec2 bCenterPos = glm::vec2(
            bTransform.position.x - (bCollider.width / 2) * bTransform.scale.x,
            bTransform.position.y - (bCollider.height / 2) * bTransform.scale.y
          );

          int aRadius = aCollider.radius * aTransform.scale.x;
          int bRadius = bCollider.radius * bTransform.scale.x;

          bool collision = CheckCircularCollision(aRadius, bRadius, aCenterPos
            , bCenterPos);

          if (collision) {
            eventManager->EmitEvent<CollisionEvent>(a, b);
          }
        }
      }
    }
    
    /**
     * @brief Checks collision between two circles.
     *
     * @param aRadius Radius of the first circle.
     * @param bRadius Radius of the second circle.
     * @param aPos Center position of the first circle.
     * @param bPos Center position of the second circle.
     *
     * @return True if the circles overlap.
     */
    bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPos
      , glm::vec2 bPos) {
      glm::vec2 dif = aPos - bPos;
      double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
      //* Hay colision si la suma de los radios es mayor a la distancia
      //* entre centros
      return (aRadius + bRadius) >= length;
    }
};

#endif  // CIRCLECOLLISIONSYSTEM_HPP