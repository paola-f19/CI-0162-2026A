#include "AnimationManager.hpp"

AnimationManager::AnimationManager() {}
AnimationManager::~AnimationManager() {}

void AnimationManager::AddAnimation(const std::string& animationId
    , const std::string& textureId, int row, int width, int height, int numFrames
    , int frameSpeedRate, bool isLoop) {

    auto animData = AnimationData(textureId, row, width, height, numFrames
        , frameSpeedRate, isLoop);

    animations[animationId] = animData;
}

AnimationData AnimationManager::GetAnimation(const std::string& animationId) {
    return animations[animationId];
}