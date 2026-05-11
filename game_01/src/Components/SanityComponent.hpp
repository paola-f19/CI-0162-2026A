#ifndef SANITYCOMPONENT_HPP
#define SANITYCOMPONENT_HPP

/**
 * @brief Defines the sanity of an entity.
 */
struct SanityComponent {
  float maxSanity;
  float currentSanity;
  float drainPerSecond;

  /**
   * @brief Constructor.
   *
   * @param maxSanity Maximum sanity.
   * @param currentSanity Current sanity.
   * @param drainPerSecond Amount of sanity decrease over time.
   */
  SanityComponent(int maxSanity = 0, int currentSanity = 0
    , int drainPerSecond = 0) {
    this->maxSanity = maxSanity;
    this->currentSanity = currentSanity;
    this->drainPerSecond = drainPerSecond;
  }
};

#endif  // SANITYCOMPONENT_HPP