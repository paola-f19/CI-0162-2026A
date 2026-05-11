#ifndef LAYERCOMPONENT_HPP
#define LAYERCOMPONENT_HPP

/**
 * @brief Defines the layer to which the entity belongs.
 */
struct LayerComponent {
  int z;

  /**
   * @brief Constructor.
   *
   * @param layer Layer where the entity exists.
   */
  LayerComponent(int layer = 0) {
    this->z = layer;
  }
};

#endif  // LAYERCOMPONENT_HPP