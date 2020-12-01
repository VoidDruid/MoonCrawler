#include "MainHeroIOSystem.h"

#include "Game/Scene.h"
#include "Subsystems/Collisions.h"
#include "Subsystems/Entities.h"

void
MoonCrawler::MainHeroIOSystem::operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, MoonCrawler::Components &components) {
    if(not entity->has<PlayerTrait>()) {
        return;
    }

    auto& transform = components.get<Transform>(entity->ID);

    sf::Vector2f lastPosition = transform.position;  // copying last position

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        transform.position.x--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        transform.position.x++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        transform.position.y++;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        transform.position.y--;
    }

    auto collisions = getCollisions(scene, entity, components);
    if (!collisions.first->empty()) {
        transform.position = lastPosition;
    }

    if (not entity->has<RangedAttack>()) {
        return;
    }

    auto& rangedAttack = components.get<RangedAttack>(entity->ID);
    auto elapsedTime = scene->getElapsedMicros();

    if (rangedAttack._lastStrikeMicros + rangedAttack.rechargeTimeSecs * MILSECS_TO_SECS > elapsedTime) {
        return;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        rangedAttack._lastStrikeMicros = elapsedTime;
        auto clickedPosition = scene->getMousePosition();
        const int shotRadius = 10;
        Transform shotTransform{
            sf::Vector2f{clickedPosition.x + shotRadius, -clickedPosition.y + shotRadius},
            sf::Vector2i{shotRadius*2, shotRadius*2}
        };

        auto iter = scene->getFitting<Transform, Health, EnemyTrait>();
        while (iter.hasValue()) {
            auto GID = iter.next();
            auto& enemyTransform = components.get<Transform>(GID);

            if (areColliding(enemyTransform, shotTransform)) {
                auto &enemyHealth = components.get<Health>(GID);
                enemyHealth.current -= rangedAttack.damage;
                qDebug() << "ENEMY HEALTH" << enemyHealth.current;
            }
        }
    }
}