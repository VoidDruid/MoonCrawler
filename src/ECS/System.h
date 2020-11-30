#pragma once

#include "Components.h"
#include "Common.h"
#include "Entity.h"

namespace MoonCrawler {
class Scene;

class System {
public:
    virtual void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) = 0;
    virtual unsigned char getNeededComponents() = 0;
};
}
