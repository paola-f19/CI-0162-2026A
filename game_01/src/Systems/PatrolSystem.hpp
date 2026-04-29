#ifndef PATROLSYSTEM_HPP
#define PATROLSYSTEM_HPP

#include "../Components/PatrolComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class PatrolSystem : public System {
  public:
    PatrolSystem() {
      RequireComponent<PatrolComponent>();
      RequireComponent<RigidBodyComponent>();
      RequireComponent<TransformComponent>();
    }

    void Update(float deltatime) {
      for (auto entity : GetSystemEntities()) {
        auto& transform = entity.GetComponent<TransformComponent>();
        auto& patrol = entity.GetComponent<PatrolComponent>();
        auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

        if (rigidbody.collided) {
          patrol.currentIndex = (patrol.currentIndex + 1) % patrol.waypoints.size();
          
          transform.position -= glm::normalize(
            patrol.waypoints[patrol.currentIndex] - transform.position
          ) * 5.0f;
          
          rigidbody.collided = false;
          continue;
        }

        glm::vec2 target = patrol.waypoints[patrol.currentIndex];
        glm::vec2 direction = target - transform.position;

        float distance = glm::length(direction);

        if (distance < 5.0f) {
          patrol.currentIndex = (patrol.currentIndex + 1) % patrol.waypoints.size();
        } else {
          direction = glm::normalize(direction);

          float moveStep = patrol.speed * deltatime;
          if (moveStep > distance) {
            moveStep = distance;
          }

          transform.position += direction * moveStep;
        }
      }
    }
};

#endif  // PATROLSYSTEM_HPP