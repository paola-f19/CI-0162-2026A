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
#include "../Components/UIComponent.hpp"
#include "../Components/UIRectComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

class UISystem : public System {
  public:
    SDL_Rect camera = { 0, 0, 0, 0 };

    UISystem() {
      RequireComponent<ClickableComponent>();
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
        const auto& transform = entity.GetComponent<TransformComponent>();

        int width = 0;
        int height = 0;

        if (entity.HasComponent<SpriteComponent>()) {
          const auto& sprite = entity.GetComponent<SpriteComponent>();
          width = sprite.width;
          height = sprite.height;
        }
        else if (entity.HasComponent<UIRectComponent>()) {
          const auto& rect = entity.GetComponent<UIRectComponent>();
          width = rect.width;
          height = rect.height;
        }
        else {
          continue;
        }

        // adjustments for camera and scale
        bool isUI = entity.HasComponent<UIComponent>();

        int x = e.posX / 2;
        int y = e.posY / 2;

        if (!isUI) {
          x += this->camera.x;
          y += this->camera.y;
        }

        if (transform.position.x < x
          && x < transform.position.x + width
          && transform.position.y < y
          && y < transform.position.y + height) {
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