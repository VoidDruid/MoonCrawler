#include "Entities.h"

namespace MoonCrawler {
void Scene::populate(const std::string& layoutName) {
    if (m_isPopulated) {
        return;  // error?
    }
    m_isPopulated = true;

    auto layoutPtr = getResource<Layout>(layoutName);

    for (auto& wall : layoutPtr->walls) {
        float adjustedX = wall.position.x + wall.size.x / 2;
        float adjustedY = wall.position.y + wall.size.y / 2;
        createStaticObject(
                shared_from_this(),
                Transform(sf::Vector2f{adjustedX, adjustedY}, wall.size),
                Collider{true},
                "wall.png");
    }
}

std::shared_ptr<StaticEntity> createStaticObject(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform,
        const std::string &textureName) {
    auto entityPtr = std::make_shared<StaticEntity>();
    GID id = scene->addObject(entityPtr);

    entityPtr->initialize(scene->getResource<Texture>(textureName), transform.size);

    scene->addComponent(id, transform);

    return entityPtr;
}

std::shared_ptr<StaticEntity> createStaticObject(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform,
        const Collider &collider,
        const std::string &textureName) {
    auto entityPtr = createStaticObject(scene, transform, textureName);

    scene->addComponent(entityPtr->ID, collider);

    return entityPtr;
}

// TODO
std::shared_ptr<StaticEntity> createPlayer(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform) {
    auto entityPtr = createStaticObject(scene, transform, TEST_TEXTURE_NAME);

    scene->addComponent(entityPtr->ID, Health{});
    scene->addComponent(entityPtr->ID, RangedAttack{});
    scene->addComponent(entityPtr->ID, PlayerTrait{});

    entityPtr->isDynamic = true;

    scene->setPlayer(entityPtr);

    return entityPtr;
}

std::shared_ptr<StaticEntity> createEnemy(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform) {
    auto entityPtr = createStaticObject(scene, transform, "test.png");

    scene->addComponent(entityPtr->ID, Health{});
    scene->addComponent(entityPtr->ID, EnemyTrait{});
    scene->addComponent(entityPtr->ID, MeleeAttack{});

    entityPtr->isDynamic = true;

    return entityPtr;
}
}