#ifndef SANITYCOMPONENT_HPP
#define SANITYCOMPONENT_HPP

struct SanityComponent {
  float maxSanity;
  float currentSanity;
  float drainPerSecond;

  SanityComponent(int maxSanity = 0, int currentSanity = 0
    , int drainPerSecond = 0) {
    this->maxSanity = maxSanity;
    this->currentSanity = currentSanity;
    this->drainPerSecond = drainPerSecond;
  }
};

#endif  // SANITYCOMPONENT_HPP