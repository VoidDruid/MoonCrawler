#include "MainHeroIOSystem.h"

#include "Scene.h"

#include <iostream>

void
MoonCrawler::MainHeroIOSystem::operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, MoonCrawler::Components &components) {
    if(not entity->isKeyboardPlayable()) {
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        auto& pos = components.positions[entity->ID];
        pos.x--;
        std::cout <<"position: " << pos.x << " " << pos.y << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        auto& pos = components.positions[entity->ID];
        pos.x++;
        std::cout <<"position: " << pos.x << " " << pos.y << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        auto& pos = components.positions[entity->ID];
        pos.y--;
        std::cout <<"position: " << pos.x << " " << pos.y << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        auto& pos = components.positions[entity->ID];
        pos.y++;
        std::cout <<"position: " << pos.x << " " << pos.y << std::endl;
    }
}