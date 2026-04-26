#ifndef HEALTHBARSYSTEM_HPP
#define HEALTHBARSYSTEM_HPP

#include "../Components/HealthBarComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class HealthBarSystem : public System {
public:
    HealthBarSystem() {
        RequireComponent<HealthComponent>();
        RequireComponent<HealthBarComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(SDL_Renderer* renderer) {
      for (auto entity : GetSystemEntities()) {
          const auto& health = entity.GetComponent<HealthComponent>();
          const auto& bar = entity.GetComponent<HealthBarComponent>();
          // const auto& transform = entity.GetComponent<TransformComponent>();

          float percent = (float)health.currentHealth / health.maxHealth;

          int fullWidth = bar.width;
          int currentWidth = static_cast<int>(fullWidth * percent);

          int x = 10;
          int y = 10;

          // Background
          SDL_Rect bgRect = { x, y, fullWidth, bar.height };
          SDL_SetRenderDrawColor(renderer, bar.bgColor.r, bar.bgColor.g
            , bar.bgColor.b, bar.bgColor.a);
          SDL_RenderFillRect(renderer, &bgRect);

          // Foreground (health)
          SDL_Rect fgRect = { x, y, currentWidth, bar.height };
          SDL_SetRenderDrawColor(renderer, bar.fgColor.r, bar.fgColor.g
            , bar.fgColor.b, bar.fgColor.a);
          SDL_RenderFillRect(renderer, &fgRect);
      }
  }
};

#endif  // HEALTHBARSYSTEM_HPP