#pragma once

#include <nlohmann/json.hpp>

#include <memory>
#include <ostream>

namespace MoonCrawler {
enum class EventType {
    Unknown,
    IOEvent,
    NetworkEvent,
    GameEvent
};

enum class EventStatus {
    Unknown,
    New,
    Stale
};

class Event {
public:
    using EventDataType = std::shared_ptr<nlohmann::json>;
    Event() = default;
    Event(const Event& event) = default;
    Event(Event&& event) noexcept;
    Event(EventDataType eventData, EventType eventType, EventStatus status);
    Event(const nlohmann::json& eventData, EventType eventType, EventStatus status);
    Event(nlohmann::json&& eventData, EventType&& eventType, EventStatus&& status) noexcept;

    [[nodiscard]] EventDataType getData() const;
    [[nodiscard]] EventType getEventType() const;
    [[nodiscard]] EventStatus getEventStatus() const;
    void markStale();

    friend std::ostream& operator<<(std::ostream& out, const EventType& eventType);
private:
    EventDataType m_data{nullptr};
    EventType m_type{EventType::Unknown};
    EventStatus m_status{EventStatus::Unknown};
};
std::ostream& operator<<(std::ostream& out, const EventType& eventType);
std::ostream& operator<<(std::ostream& out, const EventStatus& eventStatus);
std::ostream& operator<<(std::ostream& out, const Event& event);
}