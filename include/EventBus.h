#pragma once

#include "pch.h"

namespace Celestia {

/**
 * This class is rather complicated. So I am trying to
 * explain this in simpler
 * words for myself
 *
 */

class Event {
public:
  virtual ~Event() = default;
};

/**
 *
 * The EventBus has  two functions.
 *
 * The "subscribe" function is for registering actions (such as functions) which
 * should be executed when the user is pressing the responsible key on the
 * keyboard or the mouse or something else.
 * There are so called "Events". These data structures which are either empty or
 * can hold some information, which can be used as a "safe" alternative for
 * global variables. This is an example from the "Events.h" class:
 *
 * "
 * struct KeyEvent : Event {
 * SDL_Scancode scancode;
 * bool pressed;
 * KeyEvent(SDL_Scancode code, bool isPressed)
 *      : scancode(code), pressed(isPressed) {}
 * };
 * "
 *
 * This is an struct which can take a SDL_scancode and the bool if this scancode
 * key is actually pressed or not.
 *
 * The "subscribe" function, is now taking the function and calls it everytime
 * the event is triggered.alignas
 *
 *
 * The trigger for Events is happening in the "publish" function. This function
 * is called when the keypress is activated. This is an example of a publish
 * function:
 *
 * "
 *     case SDLK_ESCAPE:
 *      eventBus.publish(QuitEvent{});
 *            break;
 * "
 *
 * When the Escape key is pressed, then the "publish" function is calling the
 * QuitEvent.
 *
 * All functions, which were put into the "QuitEvent" through the "subscribe"
 * function are called. The "publish" function is checked everyframe in most
 * cases.
 *
 * */
class EventBus {

  /**
   *
   * This is like a hash map, which maps specific event like the "QuitEvent" in
   * the example above, to a dynamic array (or vector) of functions.
   * This basically means, an specific event is holding all the functions or
   * values that needs to be executed or changed, when this event is happening.
   *
   * It's like a festival where each event has its own guest list. In the same
   * way, each event type in the event bus has its own list of subscribers who
   * get notified when that event happens.
   */
  std::unordered_map<std::type_index,
                     std::vector<std::function<void(const Event &)>>>
      subscribers;

public:
  // type of the event and the function which is executed when the Event is
  // called
  template <typename EventType, typename Handler>
  void subscribe(Handler &&handler) {
    subscribers[typeid(EventType)].emplace_back(

        // creating a lambda function, which takes an Event reference an an
        // argument
        [h = std::forward<Handler>(handler)](const Event &e) {
          // if Event is the same as the base class Event, use Event. Otherwise
          // cast Event to the specific event
          if constexpr (std::is_same_v<EventType, Event>) {
            h(e);
          } else {
            h(static_cast<const EventType &>(e));
          }
        });
  }

  template <typename EventType> void publish(const EventType &event) {
    // looks for the given  Event in the hashmap. If the event has any
    // subscribers, iterate through them.

    auto it = subscribers.find(typeid(EventType));
    if (it != subscribers.end()) {
      for (auto &handler : it->second) {
        handler(event);
      }
    }
  }
};

} // namespace Celestia
