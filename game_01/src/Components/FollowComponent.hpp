#ifndef FOLLOWCOMPONENT_HPP
#define FOLLOWCOMPONENT_HPP

struct FollowComponent {
  float speed;
  float detectionRadius;

  FollowComponent(float speed = 0.0f, float detectionRadius = 0.0f) {
    this->speed = speed;
    this->detectionRadius = detectionRadius;
  }
};

#endif  // FOLLOWCOMPONENT_HPP