#ifndef WANDERSYSTEM_HPP
#define WANDERSYSTEM_HPP

#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/WanderComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Moves entities toward random targets within a defined radius.
 */
class WanderSystem : public System {
  private:
    /**
     * @brief Generates a random point inside a circular area.
     * 
     * @param origin Center point of the wander area.
     * @param radius Maximum wander distance.
     * @return Random target position.
     */
    glm::vec2 GetRandomPoint(glm::vec2 origin, float radius) {
      float angle = (float)rand() / RAND_MAX * 2.0f * M_PI;
      float dist  = (float)rand() / RAND_MAX * radius;

      return origin + glm::vec2(cos(angle), sin(angle)) * dist;
    }

  public:
    /**
     * @brief Constructor.
     */
    WanderSystem() {
      RequireComponent<WanderComponent>();
      RequireComponent<RigidBodyComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Updates wandering movement for all entities.
     * 
     * @param deltatime Time elapsed since last frame.
     */
    void Update(float deltatime) {
      for (auto entity : GetSystemEntities()) {
        auto& transform = entity.GetComponent<TransformComponent>();
        auto& wander = entity.GetComponent<WanderComponent>();
        auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

        if (rigidbody.collided) {
          transform.position = rigidbody.previousPosition;

          // pick new target
          glm::vec2 newTarget;
          do {
            newTarget = GetRandomPoint(wander.origin, wander.radius);
          } while (glm::distance(newTarget, transform.position) < 40.0f);

          wander.target = newTarget;

          rigidbody.collided = false;
          continue;
        }

        rigidbody.previousPosition = transform.position;

        // Initialize target if needed
        if (wander.target == glm::vec2(0)) {
            wander.target = GetRandomPoint(wander.origin, wander.radius);
        }

        glm::vec2 direction = wander.target - transform.position;
        float distance = glm::length(direction);

        // Reached target -> pick new one
        if (distance < 20.0f) {
            wander.target = GetRandomPoint(wander.origin, wander.radius);
            continue;
        }

        direction = glm::normalize(direction);

        // Move
        transform.position += direction * wander.speed * deltatime;
      }
    }
};

#endif  // WANDERSYSTEM_HPP