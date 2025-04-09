#pragma once
#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Event {
public:
  virtual ~Event() = default;
};

using EventHandler = std::function<void(const Event &)>;

class EventBus {

  std::unordered_map<std::type_index, std::vector<EventHandler>> subscribers;

public:
  template <typename EventType> void subscribe(EventHandler handler) {
    subscribers[typeid(EventType)].emplace_back(std::move(handler));
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
