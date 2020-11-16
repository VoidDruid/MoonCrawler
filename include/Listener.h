#pragma once

#include "Event.h"

namespace MoonCrawler {
class Listener {
public:
    virtual void onEvent(Event& event) = 0;
};
}
