#pragma once

#include "Event.h"
#include "Listener.h"

namespace MoonCrawler {
class Subscriber {
public:
    virtual void addListener(const std::shared_ptr<Listener>& listener) = 0;
    virtual ~Subscriber() = default;
};
}
