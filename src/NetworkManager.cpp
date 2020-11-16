#pragma once

#include "NetworkManager.h"
#include "GameManager.h"
#include "Event.h"

using namespace MoonCrawler;

void NetworkManager::addListener(const std::shared_ptr<Listener>& listener) {
    m_listeners.push_back(listener);
}
void NetworkManager::run() {
    auto data = R"({"game_state" : "start"})"_json;
    Event event{
            data,
            EventType::GameEvent,
            EventStatus::New};
    for(auto& listener : m_listeners) {
        listener->onEvent(event);
    }
}