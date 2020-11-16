#include "Event.h"

#include <utility>

namespace MoonCrawler {

Event::Event(EventDataType eventData, EventType eventType, EventStatus status)
    : m_data{std::move(eventData)}
    , m_type{eventType}
    , m_status{status}
{}

Event::Event(const nlohmann::json& eventData, EventType eventType, EventStatus status)
        : m_data{std::make_shared<nlohmann::json>(eventData)}
        , m_type{eventType}
        , m_status{status}
{}

Event::Event(nlohmann::json&& eventData, EventType&& eventType, EventStatus&& status) noexcept
        : m_data{std::make_shared<nlohmann::json>(eventData)}
        , m_type{eventType}
        , m_status{status}
{}

Event::Event(Event&& event) noexcept
    : m_data{std::move(event.m_data)}
    , m_type{event.m_type}
    , m_status{event.m_status}
{}

Event::EventDataType Event::getData() const {
    return m_data;
}
EventType Event::getEventType() const {
    return m_type;
}

EventStatus Event::getEventStatus() const {
    return m_status;
}

void Event::markStale() {
    m_status = EventStatus::Stale;
}

std::ostream& operator<<(std::ostream& out, const EventType& eventType) {
    switch(eventType) {
        case EventType::Unknown:
            out << "Unknown";
            break;
        case EventType::IOEvent:
            out << "IOEvent";
            break;
        case EventType::NetworkEvent:
            out << "NetworkEvent";
            break;
        case EventType::GameEvent:
            out << "GameEvent";
            break;
    }
    return out;
}


std::ostream& operator<<(std::ostream& out, const EventStatus& eventStatus) {
    switch(eventStatus) {
        case EventStatus::Unknown:
            out << "Unknown";
            break;
        case EventStatus::Stale:
            out << "Stale";
            break;
        case EventStatus::New:
            out << "New";
            break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Event& event) {
    out << "Event data: "
        << *event.getData()
        << ", Event type: "
        << event.getEventType()
        << ", Event status: "
        << event.getEventStatus() << std::endl;
    return out;
}
}