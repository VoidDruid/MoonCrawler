#pragma once

#include <memory>
#include <vector>
#include "ECS/System.h"
#include "ECS/Components.h"

namespace MoonCrawler {
using collisionsVector = std::shared_ptr<std::vector<GID>>;

std::pair<collisionsVector, collisionsVector> getCollisions(
    const std::shared_ptr<Scene>& scene,
    const std::shared_ptr<EntityBase>& entity,
    Components& components);

inline bool areColliding(const Transform& first, const Transform& second) {
    return toRect(first).intersects(toRect(second));
}
}
