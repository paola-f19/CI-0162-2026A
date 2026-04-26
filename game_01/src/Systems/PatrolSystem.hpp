#ifndef PATROLSYSTEM_HPP
#define PATROLSYSTEM_HPP

#include "../Components/PatrolComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class PatrolSystem : public System {
  public:
    PatrolSystem() {
      RequireComponent<PatrolComponent>();
      RequireComponent<TransformComponent>();
    }

    void Update(float deltatime) {
    for (auto entity : GetSystemEntities()) {
        auto& transform = entity.GetComponent<TransformComponent>();
        auto& patrol = entity.GetComponent<PatrolComponent>();

        glm::vec2 target = patrol.waypoints[patrol.currentIndex];
        glm::vec2 direction = target - transform.position;

        float distance = glm::length(direction);

        if (distance < 5.0f) {
            patrol.currentIndex = (patrol.currentIndex + 1) % patrol.waypoints.size();
        } else {
            direction = glm::normalize(direction);
            transform.position += direction * patrol.speed * deltatime;
        }
    }
  }
};

#endif  // PATROLSYSTEM_HPP