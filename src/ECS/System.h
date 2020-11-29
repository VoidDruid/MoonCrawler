#pragma once

#include "Components.h"
#include "Common.h"
#include "Entity.h"

namespace MoonCrawler {
class System {
public:
    virtual void operator()(std::shared_ptr<EntityBase> entity, Components& components) = 0;
    virtual inline unsigned char getNeededComponents() = 0;
};
}
