#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"

class AnimationSystem : public System {
    public:


        AnimationSystem() {
            RequireComponent<AnimationComponent>();
            RequireComponent<SpriteComponent>();
        }

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