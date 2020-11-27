#pragma once

#include "Components.h"

namespace MoonCrawler {
class System {
public:
    virtual void operator()(EntityID id, Components& components) = 0;
    virtual inline const unsigned char getNeededComponents() = 0;
};
}
