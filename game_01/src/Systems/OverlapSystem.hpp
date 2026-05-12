#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @brief Directions used for overlap resolution checks.
 */
enum Direction {top, left, bottom, right};

/**
 * @brief Resolves overlaps between solid entities.
 */
class OverlapSystem : public System {
  private:
    /**
     * @brief Checks collision direction between two entities.
     *
     * @param a Reference entity.
     * @param b Moving entity.
     * @param dir Direction being tested.
     *
     * @return True if the collision matches the direction.
     */
    bool CheckCollision(Entity a, Entity b, Direction dir) {
      auto& aCollider = a.GetComponent<BoxColliderComponent>();
      auto& bCollider = b.GetComponent<BoxColliderComponent>();
      auto& aTransform = a.GetComponent<TransformComponent>();
      auto& bTransform = b.GetComponent<TransformComponent>();

      float aX = aTransform.previousPosition.x + aCollider.offset.x;
      float aY = aTransform.previousPosition.y + aCollider.offset.y;
      float aW = static_cast<float>(aCollider.width);
      float aH = static_cast<float>(aCollider.height);

      float bX = bTransform.previousPosition.x + bCollider.offset.x;
      float bY = bTransform.previousPosition.y + bCollider.offset.y;
      float bW = static_cast<float>(bCollider.width);
      float bH = static_cast<float>(bCollider.height);

      // Lado superior de A choca contra el lado inferior de B
      if (Direction::top == dir) {
        return (
          aX < bX + bW &&
          aX + aW > bX &&
          aY > bY
        );
      }

      // Lado inferior de A choca contra el lado superior de B
      if (Direction::bottom == dir) {
        return (
          aX < bX + bW &&
          aX + aW > bX &&
          aY < bY
        );
      }   

      // Lado izquierdo de A choca contra el lado derecho de B
      if (Direction::left == dir) {
        return (
          aY < bY + bH &&
          aY + aH > bY &&
          aX > bX
        );
      }  

      // Lado derecho de A choca contra el lado izquierdo de B
      if (Direction::right == dir) {
        return (
          aY < bY + bH &&
          aY + aH > bY &&
          aX < bX
        );
      } 

      return false;
    }

    /**
     * @brief Repositions entities to resolve overlap.
     *
     * @param a Reference entity.
     * @param b Moving entity.
     */
    void AvoidOverlap(Entity a, Entity b) {
      auto& aCollider = a.GetComponent<BoxColliderComponent>();
      auto& aTransform = a.GetComponent<TransformComponent>();

      auto& bCollider = b.GetComponent<BoxColliderComponent>();
      auto& bTransform = b.GetComponent<TransformComponent>();
      auto& bRigidbody = b.GetComponent<RigidBodyComponent>();

      // TOP: B hits A from above -> move B up
      if (CheckCollision(a, b, Direction::top)) {
        float aTop = aTransform.position.y + aCollider.offset.y;
        float bOffsetY = bCollider.offset.y;

        bTransform.position.y = aTop - bCollider.height - bOffsetY;

        bRigidbody.velocity.y = 0.0f;
      }

      // BOTTOM: B hits A from below -> move B down
      if (CheckCollision(a, b, Direction::bottom)) {
        float aBottom = aTransform.position.y + aCollider.offset.y + aCollider.height;
        float bOffsetY = bCollider.offset.y;

        bTransform.position.y = aBottom - bOffsetY;

        bRigidbody.velocity.y = 0.0f;
      }

      // LEFT: B hits A from the left -> move B left
      if (CheckCollision(a, b, Direction::left)) {
        float aLeft = aTransform.position.x + aCollider.offset.x;
        float bOffsetX = bCollider.offset.x;

        bTransform.position.x = aLeft - bCollider.width - bOffsetX;

        bRigidbody.velocity.x = 0.0f;
      }

      // RIGHT: B hits A from the right -> move B right
      if (CheckCollision(a, b, Direction::right)) {
        float aRight = aTransform.position.x + aCollider.offset.x + aCollider.width;
        float bOffsetX = bCollider.offset.x;

        bTransform.position.x = aRight - bOffsetX;

        bRigidbody.velocity.x = 0.0f;
      }
    }

  public:
    /**
     * @brief Constructor.
     */
    OverlapSystem() {
      RequireComponent<BoxColliderComponent>();
      RequireComponent<RigidBodyComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Subscribes the system to collision events.
     *
     * @param eventManager Event manager handling subscriptions.
     */
    void SubscribeToCollisionEvent(
      const std::unique_ptr<EventManager>& eventManager) {
      eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this
        , &OverlapSystem::OnCollisionEvent);
    }

    /**
     * @brief Handles collision events and resolves overlaps.
     *
     * @param e Collision event data.
     */
    void OnCollisionEvent(CollisionEvent& e) {
      auto& aRigidbody = e.a.GetComponent<RigidBodyComponent>();
      auto& bRigidbody = e.b.GetComponent<RigidBodyComponent>();

      if (aRigidbody.isSolid && bRigidbody.isSolid) {
        if (aRigidbody.mass >= bRigidbody.mass) {
          AvoidOverlap(e.a, e.b);
        } else {
          AvoidOverlap(e.b, e.a);
        }
      }
    }
};

#endif  // OVERLAPSYSTEM_HPP