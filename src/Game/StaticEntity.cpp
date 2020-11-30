#include "StaticEntity.h"

using namespace MoonCrawler;

void StaticEntity::prepare(const std::shared_ptr<Scene> &scene) {
    if (has<Position>()) {
        auto& position = m_components->positions[ID];
        setPosition(sf::Vector2f(position.x, position.y));
    }
    auto fraction = float(scene->getDeltaMicros()) / 1000000.0f;

    rotate(360 * fraction);
}
