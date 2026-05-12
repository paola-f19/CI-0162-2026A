#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <typeindex>

#include "Event.hpp"

/**
 * @brief Base interface for event callbacks.
 */
class IEventCallback {
  private:
    /**
     * @brief Executes the callback implementation.
     *
     * @param e Event instance.
     */
    virtual void Call(Event& e) = 0;

  public:
    virtual ~IEventCallback() = default;

    /**
     * @brief Executes the callback.
     *
     * @param e Event instance.
     */
    void Execute(Event& e) {
      Call(e);
    }
};

/**
 * @brief Stores and executes a typed event callback.
 *
 * @tparam TOwner Owner class type.
 * @tparam TEvent Event type.
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
  private:
    typedef void (TOwner::*CallbackFunction)(TEvent&);

    TOwner* ownerInstance;
    CallbackFunction callbackFunction;

    /**
     * @brief Invokes the stored callback function.
     *
     * @param e Event instance.
     */
    virtual void Call(Event& e) override {
      std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
    }

  public: 
    /**
     * @brief Creates a new event callback.
     *
     * @param ownerInstance Object that owns the callback function.
     * @param callbackFunction Member function to invoke on event emission.
     */
    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
      this->callbackFunction = callbackFunction;
      this->ownerInstance = ownerInstance;
    }
};

/**
 * @brief Container storing event callback handlers.
 */
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @brief Manages event subscriptions and event dispatching.
 */
class EventManager {
  private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

  public:
    /**
     * @brief Constructor.
     */
    EventManager() {
      std::cout << "[EVENTMANAGER] Se ejecuta constructor" << std::endl;
    }

    /**
     * @brief Destructor.
     */
    ~EventManager() {
      std::cout << "[EVENTMANAGER] Se ejecuta destructor" << std::endl;
    }

    /**
     * @brief Removes all event subscriptions.
     */
    void Reset() {
      subscribers.clear();
    }

    /**
     * @brief Subscribes an object method to an event type.
     *
     * @tparam TEvent Event type.
     * @tparam TOwner Subscriber class type.
     * @param ownerInstance Subscriber instance.
     * @param callbackFunction Member function called when the event is emitted.
     */
    template <typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner* ownerInstance
      , void (TOwner::*callbackFunction)(TEvent&)) {
      if (!subscribers[typeid(TEvent)].get()) {
        subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
      }
      auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(
        ownerInstance, callbackFunction);
      subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    /**
     * @brief Emits an event to all subscribed handlers.
     *
     * @tparam TEvent Event type.
     * @tparam TArgs Event constructor argument types.
     * @param args Arguments forwarded to the event constructor.
     */
    template <typename TEvent, typename... TArgs>
    void EmitEvent(TArgs&&... args) {
      auto handlers = subscribers[typeid(TEvent)].get();
      if (handlers) {
        for (auto it = handlers->begin(); it != handlers->end(); it++) {
          auto handler = it->get();
          TEvent event(std::forward<TArgs>(args)...);
          handler->Execute(event);
        }
      }
    }
};

#endif  // EVENTMANAGER_HPP