#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include "../Components/HealthComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

class HealthSystem : public System {
  public:
    HealthSystem() {
      RequireComponent<HealthComponent>();
      RequireComponent<TagComponent>();
    }

    void Update(float deltaTime) {
      for (auto entity : GetSystemEntities()) {
        auto& health = entity.GetComponent<HealthComponent>();
        auto& tag = entity.GetComponent<TagComponent>();

        if (tag.tag == "player") {
          if (health.currentHealth <= 0 && !Game::GetInstance().isGameOver) {
            // Game::GetInstance().isGameOver = true;
            Game::GetInstance().sceneManager->SetNextScene("game_over");
            Game::GetInstance().sceneManager->StopScene();
          }
        }

        if (health.invulnerableTime > 0.0f) {
          health.invulnerableTime -= deltaTime;

          if (health.invulnerableTime < 0.0f) {
            health.invulnerableTime = 0.0f;
          }
        }
      }
    }
};

#endif  // HEALTHSYSTEM_HPP