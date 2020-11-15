#pragma once

#include "Event.h"

namespace MoonCrawler {
class Listener {
public:
    virtual void OnEvent(Event& event) = 0;
};
}
