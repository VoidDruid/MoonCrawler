#pragma once

#include "Listener.h"
#include "Subscriber.h"

#include <list>

namespace MoonCrawler {
class Event;

class GameManager : public Listener, public Subscriber {
public:
    GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    void onEvent(Event& event) override;
    void addListener(const std::shared_ptr<Listener>& listener) override;

    void startGame(bool isHost);
private:
    std::list<std::weak_ptr<Listener>> m_listeners{};
};
}