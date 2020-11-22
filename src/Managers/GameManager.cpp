#include "GameManager.h"
#include "Event.h"

#include <iostream>

using namespace MoonCrawler;

void GameManager::onEvent(Event& event) {
    std::cout << "[GameManager] onEvent: " << event << std::endl;
    auto data = *event.getData();

    if(data["gameState"] == "starting" && data["isRemote"] == true) {
        event.markStale();
        m_state = Started{};
        std::cout <<"[GameManager] Game started!" << std::endl;

        auto response = R"({"gameState" : "started"})"_json;
        response["isHost"] = m_isHost;
        response["sender"] = "GameManager";

        Event responseEvent{
                response,
                EventType::GameEvent,
                EventStatus::New};
        sendEvent(responseEvent);
    }

    if(data["gameState"] == "started" && data["isRemote"] == true) {
        event.markStale();
        m_state = Started{};
        std::cout <<"[GameManager] Game started!" << std::endl;
    }
}

void GameManager::addListener(const std::shared_ptr<Listener> &listener) {
    m_listeners.push_back(listener);
}

void GameManager::startGame(bool isHost) {
    m_state = Starting{};
    m_isHost = isHost;

    auto data = R"({"gameState" : "starting"})"_json;
    data["isHost"] = isHost;
    data["sender"] = "GameManager";

    Event event{
            data,
            EventType::GameEvent,
            EventStatus::New};
    sendEvent(event);
}

void GameManager::sendEvent(Event& event) {
    for(auto& weakListener : m_listeners) {
        if(auto listener = weakListener.lock()) {
            listener->onEvent(event);
        }
    }
}


