#ifndef RENDERUISYSTEM_HPP
#define RENDERUISYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/TransformComponent.hpp"
#include "../Components/UIRectComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderUISystem : public System {
public:
  RenderUISystem() {
    RequireComponent<UIRectComponent>();
    RequireComponent<TransformComponent>();
  }

  void Update(SDL_Renderer* renderer) {
    for (auto entity : GetSystemEntities()) {

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