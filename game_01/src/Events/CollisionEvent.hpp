#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @brief Event triggered when a collision occurs.
 */
class CollisionEvent : public Event {
  public:
    Entity a;
    Entity b;

    /**
     * @brief Constructor.
     *
     * @param a Primary entity.
     * @param b Secondary entity.
     */
    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};

#endif  // COLLISIONEVENT_HPP