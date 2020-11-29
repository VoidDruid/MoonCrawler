#pragma once

#include "Components.h"
#include "Common.h"

namespace MoonCrawler {
class System {
public:
    virtual void operator()(GID id, Components& components) = 0;
    virtual inline unsigned char getNeededComponents() = 0;
};
}
