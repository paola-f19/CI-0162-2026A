#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @brief Defines the properties of a circular collider.
 */
struct CircleColliderComponent {
  int radius;
  int width;
  int height;

  /**
   * @brief Constructor.
   *
   * @param radius Radius of collider.
   * @param width Width.
   * @param height Height.
   */
  CircleColliderComponent(int radius = 0, int width = 0, int height = 0) {
    this->radius = radius;
    this->width = width;
    this->height = height;
  }
};

#endif  // CIRCLECOLLIDERCOMPONENT_HPP