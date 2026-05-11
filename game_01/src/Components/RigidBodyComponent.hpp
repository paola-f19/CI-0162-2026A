#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Defines the properties of an entities rigidbody.
 */
struct RigidBodyComponent {
  bool isDynamic;
  bool isSolid;

  glm::vec2 sumForces = glm::vec2(0);
  glm::vec2 acceleration = glm::vec2(0);
  glm::vec2 velocity = glm::vec2(0);

  float mass;
  float invMass;

  bool collided = false;
  glm::vec2 previousPosition;

  /**
   * @brief Constructor.
   *
   * @param isDynamic True if dynamic, false otherwise.
   * @param isSolid True if solid, false otherwise.
   * @param mass Weight of the entity.
   */
  RigidBodyComponent(bool isDynamic = false, bool isSolid = false
    , float mass = 1) {
    this->isDynamic = isDynamic;
    this->isSolid = isSolid;
    this->mass = mass;
    this->invMass = 1 / mass;
  }
};

#endif  // RIGIDBODYCOMPONENT_HPP