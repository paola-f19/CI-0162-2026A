#ifndef BARSYSTEM_HPP
#define BARSYSTEM_HPP

#include "../Components/BarComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/SanityComponent.hpp"
#include "../ECS/ECS.hpp"

class BarSystem : public System {
public:
  BarSystem() {
    RequireComponent<BarComponent>();
  }

  void Update(SDL_Renderer* renderer) {
    for (auto entity : GetSystemEntities()) {
      const auto& bar = entity.GetComponent<BarComponent>();

      float current = 0.0f;
      float max = 1.0f;

      // HEALTH BAR
      if (bar.type == BarType::HEALTH &&
        entity.HasComponent<HealthComponent>()) {

        const auto& health = entity.GetComponent<HealthComponent>();

        current = health.currentHealth;
        max = health.maxHealth;
      }
      // SANITY BAR
      else if (bar.type == BarType::SANITY &&
        entity.HasComponent<SanityComponent>()) {

        const auto& sanity = entity.GetComponent<SanityComponent>();

        current = sanity.currentSanity;
        max = sanity.maxSanity;
      }

      float percent = current / max;

      int currentWidth = static_cast<int>(bar.width * percent);

      // Background
      SDL_Rect bgRect = {
        bar.posX,
        bar.posY,
        bar.width,
        bar.height
      };

      SDL_SetRenderDrawColor(
        renderer,
        bar.bgColor.r,
        bar.bgColor.g,
        bar.bgColor.b,
        bar.bgColor.a
      );

      SDL_RenderFillRect(renderer, &bgRect);

      // Foreground
      SDL_Rect fgRect = {
        bar.posX,
        bar.posY,
        currentWidth,
        bar.height
      };

      SDL_SetRenderDrawColor(
        renderer,
        bar.fgColor.r,
        bar.fgColor.g,
        bar.fgColor.b,
        bar.fgColor.a
      );

      SDL_RenderFillRect(renderer, &fgRect);
    }
  }
};

#endif  // BARSYSTEM_HPP