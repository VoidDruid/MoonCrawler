#include "Collisions.h"
#include "Game/Scene.h"

namespace MoonCrawler {

std::pair<collisionsVector, collisionsVector> getCollisions(
        const std::shared_ptr<Scene>& scene,
        const std::shared_ptr<EntityBase>& entity,
        Components& components) {

    static std::shared_ptr<std::vector<GID>> collisionsBlockingVector = std::make_shared<std::vector<GID>>();
    static std::shared_ptr<std::vector<GID>> collisionsNoneBlockingVector = std::make_shared<std::vector<GID>>();
    collisionsBlockingVector->clear();
    collisionsNoneBlockingVector->clear();

    sf::Rect<float> entityRect = toRect(components.get<Transform>(entity->ID));

    auto mappedIter = scene->getFitting<Transform, Collider>();
    while (mappedIter.hasValue()) {
        auto physEntityID = mappedIter.next();
        auto& transform = components.get<Transform>(physEntityID);
        bool isBlocking = components.get<Collider>(physEntityID).isBlocking;

        sf::Rect<float> testRect = toRect(transform);

        if (entityRect.intersects(testRect)) {
            if (isBlocking) {
                collisionsBlockingVector->push_back(physEntityID);
            }
            else {
                collisionsNoneBlockingVector->push_back(physEntityID);
            }
        }
    }

    return {collisionsBlockingVector, collisionsNoneBlockingVector};
}
};
