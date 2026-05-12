#ifndef LAYERSYSTEM_HPP
#define LAYERSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/LayerComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Manages grouped entity layers.
 */
class LayerSystem : public System {
  public:
    /**
     * @brief Constructor.
     */
    LayerSystem() {
      RequireComponent<LayerComponent>();
    }

    /**
     * @brief Removes all entities belonging to a layer.
     *
     * @param z Layer id to remove.
     */
    void RemoveLayer(int z) {
      std::cout << "[LAYERSYSTEM] entered RemoveLayer with layer " << z << std::endl;
      for (auto entity : GetSystemEntities()) {
        if (entity.HasComponent<LayerComponent>()) {
          const auto& layer = entity.GetComponent<LayerComponent>();

          // kill all entities of layer z
          if (layer.z == z) {
            entity.Kill();
          }
        }
      }
    }
};

#endif  // LAYERSYSTEM_HPP