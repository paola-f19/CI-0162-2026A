#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

/**
 * @brief Base interface for component storage pools.
 */
class IPool {
  public:
    /**
     * @brief Destructor.
     */
    virtual ~IPool() = default;
};

/**
 * @brief Stores components of a single type in contiguous memory.
 *
 * @tparam TComponent Component type stored in the pool.
 */
template <typename TComponent>
class Pool : public IPool {
  private:
    std::vector<TComponent> data;

  public:
    /**
     * @brief Constructor.
     *
     * @param size Initial pool size.
     */
    Pool(int size = 1000) {
      data.resize(size);
    }

    /**
     * @brief Destructor.
     */
    virtual ~Pool() = default;

    /**
     * @brief Checks whether the pool is empty.
     *
     * @return True if the pool contains no elements.
     */
    bool isEmpty() const {
      return data.empty();
    }

    /**
     * @brief Retrieves the current pool size.
     *
     * @return Number of stored elements.
     */
    int GetSize() const {
      return static_cast<int>(data.size());
    }

    /**
     * @brief Resizes the pool storage.
     *
     * @param n New pool size.
     */
    void Resize(int n) {
      data.resize(n);
    }

    /**
     * @brief Removes all stored components.
     */
    void Clear() {
      data.clear();
    }

    /**
     * @brief Adds a component to the pool.
     *
     * @param object Component instance to add.
     */
    void Add(TComponent object) {
      data.push_back(object);
    }

    /**
     * @brief Stores a component at a specific index.
     *
     * @param index Target index.
     * @param object Component instance to store.
     */
    void Set(int index, TComponent object) {
      data[index] = object;
    }

    /**
     * @brief Retrieves a component by index.
     *
     * @param index Component index.
     * @return Reference to the component.
     */
    TComponent& Get(unsigned int index) {
      return static_cast<TComponent&>(data[index]);
    }
 
    /**
     * @brief Accesses a component by index.
     *
     * @param index Component index.
     * @return Reference to the component.
     */
    TComponent& operator[](unsigned int index) {
      return static_cast<TComponent&>(data[index]);
    }
};

#endif  // POOL_HPP