#ifndef LIFETIMECOMPONENT_HPP
#define LIFETIMECOMPONENT_HPP

struct LifetimeComponent {
    float remainingTime;

    LifetimeComponent(float time = 0.0f) {
        remainingTime = time;
    }
};

#endif  // LIFETIMECOMPONENT_HPP