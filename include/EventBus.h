#pragma once
#include "pch.h"

namespace Celestia {

// More comments than code in this class, but I also wanna understand the code
// in the future without thinking too much about it

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

  /**
   * Creating an HandlerList, that means it holds all the callable functions
   * which are subscribed with the ".on" function
   * (In that case these will be lamdba functions).
   * std::function<> can hold any callable datatype like normal functions,
   * lamdba's etc... In that case it holds a void pointer, so the datatype is
   * not defined yet, all stored Handlers will be threated the same. This is an
   * implementation of the "Type Erasure" pattern.
   */
  using HandlerList = std::vector<std::function<void(const void *)>>;

  /**
   * This is a hashmap, every event gets an index which can be hashed and a
   * HandlerList. Basically an event points to the lambda functions which are
   * subscribed to this event
   */
  std::unordered_map<std::type_index, HandlerList> subscribers;

public:
  /**
   * The EventBus stores user-provided handlers as lambdas.
   *
   * on<TEvent>(handler) creates a wrapper lambda:
   *   auto wrapper = [h = std::forward<THandler>(handler)](const void *event) {
   *     h(*static_cast<const TEvent *>(event));
   *   };
   *
   * `h` is a variable inside the wrapper that holds the original callable
   * (lambda / function pointer / functor). `std::forward` makes sure
   * temporaries are moved and named handlers are copied. The wrapper uses
   * the uniform signature `void(const void*)`.
   *
   * When invoked (emit), the wrapper casts the `const void*` back to
   * `const TEvent*` and calls `h` with the resulting `const TEvent&`.
   * The wrapper is stored as a std::function in the subscribers map
   * under the key `typeid(TEvent)`.
   */

  /**
   * @brief Subscribe to an event type
   * @tparam TEvent The type of event to listen for (e.g., KeyEvent)
   * @tparam THandler The callback function type
   * @param handler The code to call when event happens
   *
   * Example usage:
   * @code
   * eventBus.on<KeyEvent>([](const KeyEvent& ev) {
   *   if(ev.pressed) handleKeyPress(ev.scancode);
   * });
   * @endcode
   */
  template <typename TEvent, typename THandler> void on(THandler &&handler) {
    // Create type-safe wrapper
    auto wrapper = [h = std::forward<THandler>(handler)](const void *event) {
      h(*static_cast<const TEvent *>(event));
    };

    subscribers[typeid(TEvent)].push_back(std::move(wrapper));
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
  template <typename TEvent> void emit(const TEvent &event) {
    // ".find" function returns an "end iterator" if the Event was not find.
    if (auto it = subscribers.find(typeid(TEvent)); it != subscribers.end()) {
      for (auto &handler : it->second) {
        // casting to a uniformal "const void *". The ".on" function awaits it
        handler(static_cast<const void *>(&event));
      }
    }
  }
};

} // namespace Celestia