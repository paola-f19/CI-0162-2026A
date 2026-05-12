#ifndef FOLLOWSYSTEM_HPP
#define FOLLOWSYSTEM_HPP

#include "../Components/FollowComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"

#include "../ECS/ECS.hpp"

/**
 * @brief Moves entities toward the player when nearby.
 */
class FollowSystem : public System {
public:
  /**
   * @brief Constructor.
   */
  FollowSystem() {
    RequireComponent<FollowComponent>();
    RequireComponent<RigidBodyComponent>();
    RequireComponent<TagComponent>();
    RequireComponent<TransformComponent>();
  }

  /**
   * @brief Updates follower movement behavior.
   *
   * @param deltatime Frame delta time in seconds.
   * @param playerTransform Player transform component.
   */
  void Update(float deltatime, TransformComponent& playerTransform) {
    for (auto entity : GetSystemEntities()) {
      auto& transform = entity.GetComponent<TransformComponent>();
      auto& follow    = entity.GetComponent<FollowComponent>();
      auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

      // Handle collision
      if (rigidbody.collided) {
        transform.position = rigidbody.previousPosition;
        rigidbody.collided = false;
        continue;
      }

      // Save position
      rigidbody.previousPosition = transform.position;

      // Check distance to player
      glm::vec2 toPlayer = playerTransform.position - transform.position;
      float distance = glm::length(toPlayer);

      if (distance > follow.detectionRadius) {
        continue; // player too far -> do nothing
      }

      // Move toward player
      glm::vec2 direction = glm::normalize(toPlayer);

      float moveStep = follow.speed * deltatime;
      if (moveStep > distance) {
        moveStep = distance;
      }

      transform.position += direction * moveStep;
    }
  }
};

#endif  // FOLLOWSYSTEM_HPP