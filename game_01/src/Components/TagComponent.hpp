#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP

#include <string>

/**
 * @brief Defines the tag of an entity.
 */
struct TagComponent {
  std::string tag;

  /**
   * @brief Constructor.
   *
   * @param tag String tag.
   */
  TagComponent(const std::string& tag = "")  {
    this->tag = tag;
  }
};

#endif  // TAGCOMPONENT_HPP