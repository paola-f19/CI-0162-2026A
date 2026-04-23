#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

struct HealthComponent {
    int maxHealth;
    int currentHealth;
    float invulnerableTime = 0.0f;

    HealthComponent(int maxHealth = 0, int currentHealth = 0) {
        this->maxHealth = maxHealth;
        this->currentHealth = currentHealth;
    }
};

#endif  // HEALTHCOMPONENT_HPP