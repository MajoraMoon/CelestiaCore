#pragma once
#include "pch.h"

namespace Celestia {

/**
 * @class EventBus
 * @brief The central "post office" for handling game Events
 *
 * How it works in simple terms:
 * 1. There are different "event envelopes" which can be created
 *    (like KeyEvent or QuitEvent)
 *
 * 2. Other parts of the code "subscribe" to get certain types of envelops
 *    (This is done with the "on" - function)
 *
 * 3. When something happens (like a a key press), the system "emits" the
 *    matching envelope.
 *    (This is done with the "emit" - function)
 *
 * 4. Every event which subscribed to that envelope type gets notified
 *    (These notifies can change variables, call other functions etc..)
 */
class EventBus {

  /**
   * @brief Storage for all event subscribers
   *
   * This can be imagined as a wall of mailboxes:
   * - Each mailbox is for a specific event type (KeyEvent, QuitEvent, etc..)
   * - Each mailbox contains a list of people (functions) to notify
   *
   * When the system gets a mail (emit an event), we put it in the right mailbox
   * and everyone registered there gets a copy
   */
private:
  struct HandlerWrapperBase {
    virtual ~HandlerWrapperBase() = default;
    virtual void call(const void *event) = 0;
  };

  // HandlerWrapper implements HandlerWrapperBase
  template <typename TEvent> struct HandlerWrapper : HandlerWrapperBase {
    // A "Type-Erasure-Wrapper" compatible with "(void(const TEvent&))"
    std::function<void(const TEvent &)> handler;

    HandlerWrapper(std::function<void(const TEvent &)> h)
        : handler(std::move(h)) {}
    // make sure to override the virtual funkction with the one from the
    // baseclass
    void call(const void *event) override {
      handler(*static_cast<const TEvent *>(event));
    }
  };

  std::unordered_map<std::type_index,
                     std::vector<std::unique_ptr<HandlerWrapperBase>>>
      subscribers;

public:
  /**
   * @brief Subscribe to an event type
   * @tparam TEvent The type of event to listen for (e.g., KeyEvent)
   * @tparam THandler The callback function type
   * @param handler The function to call when event happens
   *
   * Example usage:
   * @code
   * eventBus.on<KeyEvent>([](const KeyEvent& ev) {
   *   if(ev.pressed) handleKeyPress(ev.scancode);
   * });
   * @endcode
   */
  template <typename TEvent, typename THandler> void on(THandler &&handler) {
    using EventType = std::decay_t<TEvent>;

    // Create a type-safe wrapper for this specific event type
    auto wrapper = std::make_unique<HandlerWrapper<EventType>>(
        [h = std::forward<THandler>(handler)](const EventType &e) { h(e); });

    // Add to subscribers list for this event type
    subscribers[typeid(EventType)].push_back(std::move(wrapper));
  }

  /**
   * @brief Send out an event notification
   * @tparam EventType The type of event to send
   * @param event The actual event data to distribute
   *
   * Example usage when ESC key is pressed:
   * @code
   * eventBus.emit(QuitEvent{});
   * @endcode
   *
   * This would notify everyone who subscribed to QuitEvent events.
   */
  template <typename EventType> void emit(const EventType &event) {
    auto it = subscribers.find(typeid(EventType));
    if (it != subscribers.end()) {
      // Send event to all subscribers like delivering mail
      for (auto &wrapper : it->second) {
        wrapper->call(&event);
      }
    }
  }
};

} // namespace Celestia