#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @brief Describes an entity that should be clickable.
 */
struct ClickableComponent {
  bool isClicked;

  /**
   * @brief Constructor.
   */
  ClickableComponent() {
    isClicked = false;
  }
};

#endif  // CLICKABLECOMPONENT_HPP