#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @brief Event triggered when a mouse button is pressed.
 */
class ClickEvent : public Event {
  public:
    int buttonCode;
    int posX;
    int posY;

    /**
     * @brief Constructor.
     *
     * @param buttonCode SDL mouse button code.
     * @param posX Horizontal mouse position.
     * @param posY Vertical mouse position.
     */
    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0) {
      this->buttonCode = buttonCode;
      this->posX = posX;
      this->posY = posY;
    }
};

#endif  // CLICKEVENT_HPP