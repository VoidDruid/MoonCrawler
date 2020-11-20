#pragma once

#include <list>

#include "Listener.h"
#include "Event.h"
#include "NetworkPAL/INetworkPAL.h"
#include "Subscriber.h"

namespace MoonCrawler {
class NetworkManager : public Subscriber, public Listener {
public:
    NetworkManager();
    void init();
    void addListener(const std::shared_ptr<Listener>& listener) override;
    void startServer();
    void startClient();
    void sendEvent(const Event& data);
    void onEvent(Event& event) override;
private:
    void startPAL(bool isServer);
    static void onDataReceivedCallback(void* self, const char* data);
    void onDataReceived(Event& event);

    void sendStartUpRequest();

    std::list<std::weak_ptr<Listener>> m_listeners{};
    std::shared_ptr<INetworkPAL> m_networkPAL{nullptr};

};
}