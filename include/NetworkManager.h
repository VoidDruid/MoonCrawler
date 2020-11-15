#pragma once

#include <list>

#include "Listener.h"

namespace MoonCrawler {
class NetworkManager {
public:
    void AddListener(const std::shared_ptr<Listener>& listener);
    void Run();
private:
    std::list<std::shared_ptr<Listener>> m_listeners{};
};
}