#ifndef PLAYERSYSTEM_HPP
#define PLAYERSYSTEM_HPP

#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Stores and provides access to the player entity.
 */
class PlayerSystem : public System {
  private:
    TransformComponent* playerTransform;
    Entity player{-1};

  public:
    /**
     * @brief Constructor.
     */
    PlayerSystem() {
      RequireComponent<TagComponent>();
      RequireComponent<TransformComponent>();
    }

    /**
     * @brief Searches for the player entity.
     */
    void Update() {
      for (auto entity : GetSystemEntities()) {
        auto& tag = entity.GetComponent<TagComponent>();

        if (tag.tag == "player") {
          playerTransform = &entity.GetComponent<TransformComponent>();
          player = entity;
          break;
        }
      }
    }

    /**
     * @brief Returns the player's transform component.
     *
     * @return Reference to the player's transform.
     */
    TransformComponent& GetPlayerTransform() const {
      return *playerTransform;
    }

    /**
     * @brief Returns the player entity.
     *
     * @return Player entity.
     */
    Entity GetPlayer() const {
      return player;
    }
};

#endif 