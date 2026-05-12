#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Updates sprite animations for entities.
 */
class AnimationSystem : public System {
  public:

    /**
     * @brief Constructor.
     */
    AnimationSystem() {
      RequireComponent<AnimationComponent>();
      RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Updates all active entity animations.
     *
     * @param animationManager Animation manager containing animation data.
     */
    void Update(std::unique_ptr<AnimationManager>& animationManager) {
      for (auto entity : GetSystemEntities()) {
        auto& animation = entity.GetComponent<AnimationComponent>();
        auto& sprite = entity.GetComponent<SpriteComponent>();

        const auto& data = animationManager->GetAnimation(animation.animationId);

        int frame = ((SDL_GetTicks() - animation.startTime)
          * data.frameSpeedRate / 1000);

        if (data.isLoop) {
          frame %= data.numFrames;
        } else {
          frame = std::min(frame, data.numFrames - 1);
        }

        animation.currentFrame = frame;

        sprite.srcRect.x = frame * data.width;
        sprite.srcRect.y = data.row * data.height;
        sprite.srcRect.w = data.width;
        sprite.srcRect.h = data.height;

        //  Destination size
        sprite.width  = data.width;
        sprite.height = data.height;
      }
    }
};

#endif  // ANIMATIONSYSTEM_HPP