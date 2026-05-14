#ifndef RENDERUISYSTEM_HPP
#define RENDERUISYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/PauseMenuComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/UIRectComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

/**
 * @brief Renders UI rectangles to the screen.
 */
class RenderUISystem : public System {
  public:
    /**
     * @brief Constructor.
     */
    RenderUISystem() {
      RequireComponent<UIRectComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Renders all UI rectangles.
     *
     * @param renderer SDL renderer used for drawing.
     */
    void Update(SDL_Renderer* renderer) {
      for (auto entity : GetSystemEntities()) {

        // pause menu check
        bool isPauseMenuEntity = entity.HasComponent<PauseMenuComponent>();
        if (isPauseMenuEntity && !Game::GetInstance().isPaused) {
          continue;
        }

        const auto& rect = entity.GetComponent<UIRectComponent>();
        const auto& transform = entity.GetComponent<TransformComponent>();

        SDL_Rect dstRect = {
            (int)transform.position.x,
            (int)transform.position.y,
            rect.width,
            rect.height
        };

        SDL_SetRenderDrawColor(
            renderer,
            rect.color.r,
            rect.color.g,
            rect.color.b,
            rect.color.a
        );

        SDL_RenderFillRect(renderer, &dstRect);
      }
    }
};

#endif  // RENDERUISYSTEM_HPP