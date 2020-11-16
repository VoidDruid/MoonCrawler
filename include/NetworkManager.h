#pragma once

#include <list>

#include "Listener.h"

namespace MoonCrawler {
class NetworkManager {
public:
    void addListener(const std::shared_ptr<Listener>& listener);
    void run();
private:
    std::list<std::shared_ptr<Listener>> m_listeners{};
};
}