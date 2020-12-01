#pragma once

#include <memory>
#include <vector>
#include "ECS/System.h"

namespace MoonCrawler {
using collisionsVector = std::shared_ptr<std::vector<GID>>;

std::pair<collisionsVector, collisionsVector> getCollisions(
    const std::shared_ptr<Scene>& scene,
    const std::shared_ptr<EntityBase>& entity,
    Components& components);
}


