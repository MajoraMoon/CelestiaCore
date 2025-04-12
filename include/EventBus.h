#pragma once

#include "pch.h"

class Event {
public:
  virtual ~Event() = default;
};

using EventHandler = std::function<void(const Event &)>;

class EventBus {

  std::unordered_map<std::type_index,
                     std::vector<std::function<void(const Event &)>>>
      subscribers;

public:
  template <typename EventType, typename Handler>
  void subscribe(Handler &&handler) {
    subscribers[typeid(EventType)].emplace_back(
        [h = std::forward<Handler>(handler)](const Event &e) {
          if constexpr (std::is_same_v<EventType, Event>) {
            h(e);
          } else {
            h(static_cast<const EventType &>(e));
          }
        });
  }

  template <typename EventType> void publish(const EventType &event) {
    auto it = subscribers.find(typeid(EventType));
    if (it != subscribers.end()) {
      for (auto &handler : it->second) {
        handler(event);
      }
    }
  }
};
