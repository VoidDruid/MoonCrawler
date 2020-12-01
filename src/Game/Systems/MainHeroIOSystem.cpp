#include "MainHeroIOSystem.h"

#include "Game/Scene.h"
#include "Subsystems/Collisions.h"

void
MoonCrawler::MainHeroIOSystem::operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, MoonCrawler::Components &components) {
    if(not entity->isKeyboardPlayable()) {
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
}