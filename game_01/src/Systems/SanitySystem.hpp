#ifndef SANITYSYSTEM_HPP
#define SANITYSYSTEM_HPP

#include "../Components/SanityComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

class SanitySystem : public System {
  public:
    SanitySystem() {
      RequireComponent<SanityComponent>();
    }

  void Update(float deltaTime) {
    for (auto entity : GetSystemEntities()) {
      auto& sanity = entity.GetComponent<SanityComponent>();

      sanity.currentSanity -= sanity.drainPerSecond * deltaTime;

      sanity.currentSanity = std::max(0.0f, sanity.currentSanity);

      // lose if runs out of sanity
      if (sanity.currentSanity <= 0) {
        Game::GetInstance().sceneManager->SetNextScene("game_over");
        Game::GetInstance().sceneManager->StopScene();
      }
    }
  }
};

#endif  // SANITYSYSTEM_HPP