#ifndef RENDERBOXCOLLIDERSYSTEM
#define RENDERBOXCOLLIDERSYSTEM

#include <SDL2/SDL.h>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Renders debug box colliders on screen.
 */
class RenderBoxColliderSystem : public System {
  public:
    /**
     * @brief Creates a new box collider render system.
     */
    RenderBoxColliderSystem() {
      RequireComponent<BoxColliderComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Renders all box colliders.
     *
     * @param renderer SDL renderer used for drawing.
     * @param camera Current camera rectangle.
     */
    void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
      for (auto entity : GetSystemEntities()) {
        const auto& collider = entity.GetComponent<BoxColliderComponent>();
        const auto& transform = entity.GetComponent<TransformComponent>();

        SDL_Rect box = {
          static_cast<int>(transform.position.x + collider.offset.x - camera.x),
          static_cast<int>(transform.position.y + collider.offset.y - camera.y),
          static_cast<int>(collider.width * transform.scale.x),
          static_cast<int>(collider.height * transform.scale.y)
        };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &box);
      }
    }
};

#endif  // RENDERBOXCOLLIDERSYSTEM