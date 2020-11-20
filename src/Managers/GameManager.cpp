#include "GameManager.h"
#include "Event.h"

#include <iostream>

using namespace MoonCrawler;

void GameManager::onEvent(Event& event) {
    std::cout << "onEvent: " << event << std::endl;
    event.markStale();
}

void GameManager::addListener(const std::shared_ptr<Listener> &listener) {
    m_listeners.push_back(listener);
}

void GameManager::startGame(bool isHost) {
    auto data = R"({"gameState" : "start"})"_json;
    data["isHost"] = isHost;
    data["sender"] = "GameManager";

    Event event{
            data,
            EventType::GameEvent,
            EventStatus::New};

    for(auto& weakListener : m_listeners) {
        if(auto listener = weakListener.lock()) {
            listener->onEvent(event);
        }
    }
}
