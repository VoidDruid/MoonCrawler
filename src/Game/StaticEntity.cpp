#include "StaticEntity.h"

using namespace MoonCrawler;

void StaticEntity::prepare(const std::shared_ptr<Scene>& scene) {
    if (has<Transform>()) {
        auto& transform = m_components->get<Transform>(ID);
        setPosition(transform.position.x * PIXELS_PER_UNIT, -transform.position.y * PIXELS_PER_UNIT);
        setSize(transform.size * PIXELS_PER_UNIT);  // TODO: optimize
    }
}
