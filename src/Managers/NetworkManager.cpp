#include "NetworkManager.h"
#include "src/Managers/GameManager.h"
#include "Event.h"
#include "NetworkPAL/NetworkLinuxPAL.h"

#include <thread>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

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
    m_isHost = isServer;
    if(isServer) {
        m_networkPAL->initServer("ss", 9999);
    }
    else {
        m_networkPAL->initClient("ss", 9999);
    }
}

void NetworkManager::sendEvent(Event &data) {
    std::stringstream stream;
    int type = static_cast<int>(data.getEventType());
    auto eventData = *data.getData();
    eventData["isRemote"] = true;
    stream << type << eventData;
    m_networkPAL->sendData(stream.str().c_str());
}

void NetworkManager::onDataReceivedCallback(void *self, const char *data) {
    auto* myself = (NetworkManager*)self;
    std::stringstream stream{};
    int eventType{};
    stream << data[0];
    stream >> eventType;
    Event event{
            nlohmann::json::parse(data+1),
            EventType(eventType),
            EventStatus::New};
    auto& eventData = *event.getData();
    eventData["isRemote"] = true;

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
    if(eventData["gameState"] == "starting" && event.getEventStatus() == EventStatus::New) {
        sendStartUpRequest(event);
        return;
    }
    sendEvent(event);

}

void NetworkManager::sendStartUpRequest(Event &event) {
    auto eventData = *event.getData();
    if(eventData["isHost"] == true) {
        startServer();
    }
    else {
        startClient();
    }
    constexpr uint8_t MAX_RETRIES = 5;
    uint8_t retry{};

    while(!m_networkPAL->isConnected() && retry < MAX_RETRIES) {
        std::cout << "Connectivity issue. Retry: " << (int)retry << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        retry++;
    }

    if(retry == MAX_RETRIES) {
        std::cerr << "Error! Cannot connect to peer!" << std::endl;
    }
    std::cout << "Initialized!" << std::endl;
    sendEvent(event);
}
