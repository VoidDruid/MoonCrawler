#pragma once

#include <list>
#include <memory>

#include "Listener.h"
#include "Event.h"
#include "NetworkPAL/INetworkPAL.h"
#include "Subscriber.h"

namespace MoonCrawler {
class NetworkManager : public Subscriber, public Listener, public std::enable_shared_from_this<NetworkManager> {
public:
    NetworkManager();
    void init();
    void addListener(const std::shared_ptr<Listener>& listener) override;
    void startServer();
    void startClient();
    void sendEvent(Event& data);
    void onEvent(Event& event) override;
    ~NetworkManager() = default;
private:
    void startPAL(bool isServer);
    static void onDataReceivedCallback(void* self, const char* data);
    void onDataReceived(Event& event);

    void sendStartUpRequest(Event &event);

    std::list<std::weak_ptr<Listener>> m_listeners{};
    std::shared_ptr<INetworkPAL> m_networkPAL{nullptr};
    bool m_isHost{false};
};

std::shared_ptr<NetworkManager> getNetworkManager();
}