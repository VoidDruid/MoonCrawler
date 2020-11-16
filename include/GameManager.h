#pragma once

#include "Listener.h"

namespace MoonCrawler {
class Event;
class GameManager : public Listener {
public:
    GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    void onEvent(Event& event) override;
private:
};
}