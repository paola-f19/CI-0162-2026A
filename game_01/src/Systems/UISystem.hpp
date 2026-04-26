#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <string>

#include "../Components/ClickableComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

class UISystem : public System {
  public:
    SDL_Rect camera = { 0, 0, 0, 0 };

    UISystem() {
      RequireComponent<ClickableComponent>();
      RequireComponent<SpriteComponent>();
      // RequireComponent<TextComponent>();
      RequireComponent<TransformComponent>();
    }

    void Update(SDL_Rect& camera) {
      this->camera = camera;
    }

    void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
      eventManager->SubscribeToEvent<ClickEvent, UISystem>(this
        , &UISystem::OnClickEvent);
    }

    void OnClickEvent(ClickEvent& e) {
      for (auto entity : GetSystemEntities()) {
        const auto& sprite = entity.GetComponent<SpriteComponent>();
        const auto& transform = entity.GetComponent<TransformComponent>();

        // adjustments for camera and scale
        int worldX = (e.posX / 2) + this->camera.x;
        int worldY = (e.posY / 2) + this->camera.y;

        if (transform.position.x < worldX
          && worldX < transform.position.x + sprite.width
          && transform.position.y < worldY
          && worldY < transform.position.y + sprite.height) {
          if (entity.HasComponent<ScriptComponent>()) {
            const auto& script = entity.GetComponent<ScriptComponent>();
            if (script.onClick != sol::nil) {
              script.onClick();
            }
          }
        }
      }
    }
};

#endif  // UISYSTEM_HPP