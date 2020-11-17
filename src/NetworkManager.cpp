#pragma once

#include "NetworkManager.h"
#include "GameManager.h"
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
void NetworkManager::run() {
    std::thread t1(&NetworkManager::startPAL, this);
    t1.detach();
}
void NetworkManager::startPAL() {
    m_networkPAL->initServer("ss", 9999);
}

void NetworkManager::sendData(const Event &data) {
    std::stringstream stream;
    stream << *data.getData();
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
    for(auto& listener : m_listeners) {
        listener->onEvent(event);
    }

}