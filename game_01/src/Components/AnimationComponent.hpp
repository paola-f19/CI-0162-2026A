#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

struct AnimationComponent {
  std::string animationId;
  int currentFrame;
  int startTime;

  AnimationComponent(std::string id = "") {
      this->animationId = id;
      this->currentFrame = 1;
      this->startTime = SDL_GetTicks();
  }
};

#endif  // ANIMATIONCOMPONENT_HPP