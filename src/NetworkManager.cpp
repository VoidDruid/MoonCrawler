#pragma once

#include "NetworkManager.h"
#include "GameManager.h"
#include "Event.h"

using namespace MoonCrawler;

void NetworkManager::AddListener(const std::shared_ptr<Listener>& listener) {
    m_listeners.push_back(listener);
}
void NetworkManager::Run() {
    auto data = R"({"game_state" : "start"})"_json;
    Event event{
            data,
            EventType::GameEvent,
            EventStatus::Unknown};
    for(auto& listener : m_listeners) {
        listener->OnEvent(event);
    }
}