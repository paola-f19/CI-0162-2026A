#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include <memory>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

enum Direction {top, left, bottom, right};

class OverlapSystem : public System {
    private:
        bool CheckCollision(Entity a, Entity b, Direction dir) {
            auto& aCollider = a.GetComponent<BoxColliderComponent>();
            auto& bCollider = b.GetComponent<BoxColliderComponent>();
            auto& aTransform = a.GetComponent<TransformComponent>();
            auto& bTransform = b.GetComponent<TransformComponent>();

            float aX = aTransform.previousPosition.x;
            float aY = aTransform.previousPosition.y;
            float aW = static_cast<float>(aCollider.width);
            float aH = static_cast<float>(aCollider.height);

            float bX = bTransform.previousPosition.x;
            float bY = bTransform.previousPosition.y;
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

        void AvoidOverlap(Entity a, Entity b) {
            auto& aCollider = a.GetComponent<BoxColliderComponent>();
            auto& aTransform = a.GetComponent<TransformComponent>();

            auto& bCollider = b.GetComponent<BoxColliderComponent>();
            auto& bTransform = b.GetComponent<TransformComponent>();
            auto& bRigidbody = b.GetComponent<RigidBodyComponent>();

            if (CheckCollision(a, b, Direction::top)) {
                // Se mueve la entidad b hacia arriba
                bTransform.position = glm::vec2(bTransform.position.x
                    , aTransform.position.y - bCollider.height);
                bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);
            }

            if (CheckCollision(a, b, Direction::bottom)) {
                // Se mueve la entidad b hacia abajo
                bTransform.position = glm::vec2(bTransform.position.x
                    , aTransform.position.y + aCollider.height);
                bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);
            }

            if (CheckCollision(a, b, Direction::left)) {
                bTransform.position = glm::vec2(aTransform.position.x - bCollider.width
                    , bTransform.position.y);
                bRigidbody.velocity = glm::vec2(0.0f, bRigidbody.velocity.y);
            }

            if (CheckCollision(a, b, Direction::right)) {
                bTransform.position = glm::vec2(aTransform.position.x + aCollider.width
                    , bTransform.position.y);
                bRigidbody.velocity = glm::vec2(0.0f, bRigidbody.velocity.y);
            }
        }

    public:
        OverlapSystem() {
            RequireComponent<BoxColliderComponent>();
            RequireComponent<RigidBodyComponent>();
            RequireComponent<TransformComponent>();
        }

        void SubscribeToCollisionEvent(
            const std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this
                , &OverlapSystem::OnCollisionEvent);
        }

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