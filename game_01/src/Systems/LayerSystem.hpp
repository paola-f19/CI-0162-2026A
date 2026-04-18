#ifndef LAYERSYSTEM_HPP
#define LAYERSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/LayerComponent.hpp"
#include "../ECS/ECS.hpp"

class LayerSystem : public System {
    public:
        LayerSystem() {
            RequireComponent<LayerComponent>();
        }

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