#pragma once

#include <list>

#include "Listener.h"
#include "Event.h"
#include "NetworkPAL/INetworkPAL.h"

namespace MoonCrawler {
class NetworkManager {
public:
    NetworkManager();
    void init();
    void addListener(const std::shared_ptr<Listener>& listener);
    void run();
    void sendData(const Event& data);
private:
    void startPAL();
    static void onDataReceivedCallback(void* self, const char* data);
    void onDataReceived(Event& event);

    std::list<std::shared_ptr<Listener>> m_listeners{};
    std::shared_ptr<INetworkPAL> m_networkPAL{nullptr};

};
}