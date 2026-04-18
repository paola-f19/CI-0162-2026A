#ifndef LAYERCOMPONENT_HPP
#define LAYERCOMPONENT_HPP

struct LayerComponent {
    int z;

    LayerComponent(int layer = 0) {
        this->z = layer;
        // std::cout << "[LAYERCOMPONENT] created layer with z = " << layer << std::endl;
    }
};

#endif  // LAYERCOMPONENT_HPP