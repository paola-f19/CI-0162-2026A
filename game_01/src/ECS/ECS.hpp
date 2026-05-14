#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <deque>
#include <iostream>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "../Utils/Pool.hpp"

/**
 * @file ECS.hpp
 * @brief Core Entity Component System architecture.
 */

const unsigned int MAX_COMPONENTS = 64;

// Signature
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Base interface for component identification.
 */
struct IComponent {
  protected:
    static int nextId;
};

/**
 * @brief Generates unique ids for component types.
 *
 * @tparam TComponent Component type.
 */
template <typename TComponent>
class Component : public IComponent {
  public:
    /**
     * @brief Retrieves the unique id of a component type.
     *
     * @return Component type id.
     */
    static int GetId() {
      static int id = nextId++;
      return id;
    }
};

/**
 * @brief Represents an entity within the ECS.
 */
class Entity {
  private:
    int id;

  public:
    /**
     * @brief Constructor.
     *
     * @param id Unique entity id.
     */
    Entity(int id) : id(id) {}

    /**
     * @brief Getter for entity id.
     *
     * @return Entity id.
     */
    int GetId() const;

    /**
     * @brief Marks the entity for removal.
     */
    void Kill();

    bool operator==(const Entity& other) const {return id == other.id; } 
    bool operator!=(const Entity& other) const {return id != other.id; }
    bool operator>(const Entity& other) const {return id > other.id; }
    bool operator<(const Entity& other) const {return id < other.id; }

    /**
     * @brief Adds a component to the entity.
     *
     * @tparam TComponent Component type.
     * @tparam TArgs Component constructor argument types.
     * @param args Arguments forwarded to the component constructor.
     */
    template <typename TComponent, typename... TArgs>
    void AddComponent(TArgs&&... args);

    /**
     * @brief Removes a component from the entity.
     *
     * @tparam TComponent Component type.
     */
    template <typename TComponent>
    void RemoveComponent();

    /**
     * @brief Checks whether the entity has a component.
     *
     * @tparam TComponent Component type.
     * @return True if the entity has the component.
     */
    template <typename TComponent>
    bool HasComponent() const;

    /**
     * @brief Retrieves a component from the entity.
     *
     * @tparam TComponent Component type.
     * @return Reference to the requested component.
     */
    template <typename TComponent>
    TComponent& GetComponent() const;

    class Registry* registry;
};

/**
 * @brief Base class for ECS systems.
 */
class System {
  private:
    Signature componentSignature;
    std::vector<Entity> entities;

  public:
    System() = default;
    ~System() = default;

    /**
     * @brief Adds an entity to the system.
     *
     * @param entity Entity to add.
     */
    void AddEntityToSystem(Entity entity);

    /**
     * @brief Removes an entity from the system.
     *
     * @param entity Entity to remove.
     */
    void RemoveEntityFromSystem(Entity entity);

    /**
     * @brief Clears all entities from the system.
     */
    void ClearEntities();

    /**
     * @brief Retrieves all entities managed by the system.
     *
     * @return Vector of entities.
     */
    std::vector<Entity> GetSystemEntities() const;

    /**
     * @brief Retrieves the required component signature.
     *
     * @return Component signature.
     */
    const Signature& GetComponentSignature() const;

    /**
     * @brief Declares a required component for the system.
     *
     * @tparam TComponent Required component type.
     */
    template <typename TComponent>
    void RequireComponent();
};

/**
 * @brief Central manager for entities, components, and systems.
 */
class Registry {
  private:
    int numEntity = 0;

    std::vector<std::shared_ptr<IPool>> componentsPools;
    std::vector<Signature> entityComponentSignatures;

    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

    std::deque<int> freeIds;
  
  public:
    /**
     * @brief Constructor.
     */
    Registry();
    /**
     * @brief Destructor.
     */
    ~Registry();

    /**
     * @brief Updates entity and system state.
     */
    void Update();

    //* Entity management

    /**
     * @brief Creates a new entity.
     *
     * @return Newly created entity.
     */
    Entity CreateEntity();

    /**
     * @brief Marks an entity for removal.
     *
     * @param entity Entity to remove.
     */
    void KillEntity(Entity entity);

    //* Component management

    /**
     * @brief Adds a component to an entity.
     *
     * @tparam TComponent Component type.
     * @tparam TArgs Component constructor argument types.
     * @param entity Target entity.
     * @param args Arguments forwarded to the component constructor.
     */
    template <typename TComponent, typename... TArgs>
    void AddComponent(Entity entity, TArgs&&... args);

    /**
     * @brief Removes a component from an entity.
     *
     * @tparam TComponent Component type.
     * @param entity Target entity.
     */
    template <typename TComponent>
    void RemoveComponent(Entity entity);

    /**
     * @brief Checks whether an entity owns a component.
     *
     * @tparam TComponent Component type.
     * @param entity Target entity.
     * @return True if the entity owns the component.
     */
    template <typename TComponent>
    bool HasComponent(Entity entity) const;

    /**
     * @brief Retrieves a component from an entity.
     *
     * @tparam TComponent Component type.
     * @param entity Target entity.
     * @return Reference to the requested component.
     */
    template <typename TComponent>
    TComponent& GetComponent(Entity entity) const;

    //* System management

    /**
     * @brief Registers a system.
     *
     * @tparam TSystem System type.
     * @tparam TArgs System constructor argument types.
     * @param args Arguments forwarded to the system constructor.
     */
    template <typename TSystem, typename... TArgs>
    void AddSystem(TArgs&&... args);

    /**
     * @brief Removes a system.
     *
     * @tparam TSystem System type.
     */
    template <typename TSystem>
    void RemoveSystem();

    /**
     * @brief Checks whether a system is registered.
     *
     * @tparam TSystem System type.
     * @return True if the system exists.
     */
    template <typename TSystem>
    bool HasSystem() const;

    /**
     * @brief Retrieves a registered system.
     *
     * @tparam TSystem System type.
     * @return Reference to the requested system.
     */
    template <typename TSystem>
    TSystem& GetSystem() const;

    /**
     * @brief Adds an entity to matching systems.
     *
     * @param entity Entity to add.
     */
    void AddEntityToSystems(Entity entity);

    /**
     * @brief Removes an entity from all systems.
     *
     * @param entity Entity to remove.
     */
    void RemoveEntityFromSystems(Entity entity);

    /**
     * @brief Removes all entities from the registry.
     */
    void ClearAllEntities();
};

template <typename TComponent>
void System::RequireComponent() {
  const int componentId = Component<TComponent>::GetId();
  componentSignature.set(componentId);
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args) {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();

  if (static_cast<long unsigned int>(componentId) >= componentsPools.size()) {
    componentsPools.resize(componentId + 10, nullptr);
  }

  if (!componentsPools[componentId]) {
    std::shared_ptr<Pool<TComponent>> newComponentPool
      = std::make_shared<Pool<TComponent>>();
    componentsPools[componentId] = newComponentPool;
  }

  std::shared_ptr<Pool<TComponent>> componentPool
    = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
  
  if (entityId >= componentPool->GetSize()) {
    componentPool->Resize(numEntity + 100);
  }

  TComponent newComponent(std::forward<TArgs>(args)...);

  componentPool->Set(entityId, newComponent);
  entityComponentSignatures[entityId].set(componentId);

  // std::cout << "[REGISTRY] Se agrega componente " << componentId 
  //  << " a la entidad " << entityId << std::endl;
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();

  entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();

  return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const {
  const int componentId = Component<TComponent>::GetId();
  const int entityId = entity.GetId();

  auto componentPool
    = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
  
  return componentPool->Get(entityId);
}

template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args) {
  std::shared_ptr<TSystem> newSystem
    = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
  systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem() {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const {
  return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem() const {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs&&... args) {
  registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::RemoveComponent() {
  registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const {
  return registry->HasComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent& Entity::GetComponent() const {
  return registry->GetComponent<TComponent>(*this);
}

#endif  // ECS_HPP