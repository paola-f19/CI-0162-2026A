#ifndef PLAYERSYSTEM_HPP
#define PLAYERSYSTEM_HPP

#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class PlayerSystem : public System {
private:
  TransformComponent* playerTransform;

public:
  PlayerSystem() {
    RequireComponent<TagComponent>();
    RequireComponent<TransformComponent>();
  }

  void Update() {
    for (auto entity : GetSystemEntities()) {
      auto& tag = entity.GetComponent<TagComponent>();

      if (tag.tag == "player") {
        playerTransform = &entity.GetComponent<TransformComponent>();
        break;
      }
    }
  }

  TransformComponent& GetPlayerTransform() const {
    return *playerTransform;
  }
};

#endif 