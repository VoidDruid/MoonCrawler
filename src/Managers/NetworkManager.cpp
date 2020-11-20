#pragma once

#include "NetworkManager.h"
#include "src/Managers/GameManager.h"
#include "Event.h"
#include "NetworkPAL/NetworkLinuxPAL.h"

#include <thread>
#include <sstream>

using namespace MoonCrawler;

NetworkManager::NetworkManager()
    : m_networkPAL(std::make_shared<NetworkLinuxPAL>())
{}

void NetworkManager::init() {
    m_networkPAL->setReceiveCallback(this, NetworkManager::onDataReceivedCallback);
}

void NetworkManager::addListener(const std::shared_ptr<Listener>& listener) {
    m_listeners.push_back(listener);
}

void NetworkManager::startPAL(bool isServer) {
    if(isServer) {
        m_networkPAL->initServer("ss", 9999);
    }
    else {
        m_networkPAL->initClient("ss", 9999);
    }
}

void NetworkManager::sendEvent(const Event &data) {
    std::stringstream stream;
    int type = static_cast<int>(data.getEventType());
    stream << type << *data.getData();
    m_networkPAL->sendData(stream.str().c_str());
}

void NetworkManager::onDataReceivedCallback(void *self, const char *data) {
    auto* myself = (NetworkManager*)self;
    std::stringstream stream{};
    int eventType{};
    stream << data[0];
    stream >> eventType;
    Event event{
            data+1,
            EventType(eventType),
            EventStatus::New};

    myself->onDataReceived(event);

}

void NetworkManager::onDataReceived(Event& event) {
    for(auto& weakListener : m_listeners) {
        if(auto listener = weakListener.lock()) {
            listener->onEvent(event);
        }
    }
}

void NetworkManager::startServer() {
    std::thread t1(&NetworkManager::startPAL, this, true);
    t1.detach();
}

void NetworkManager::startClient() {
    std::thread t1(&NetworkManager::startPAL, this, false);
    t1.detach();
}

void NetworkManager::onEvent(Event &event) {
    auto eventData = *event.getData();
    if(eventData["gameState"] == "start") {
        if(eventData["isHost"] == true) {
            startServer();
        }
        else {
            startClient();
        }
    }
}

void NetworkManager::sendStartUpRequest() {
    
}
