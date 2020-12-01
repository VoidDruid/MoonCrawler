#include "HealthSystem.h"

#include "Game/Scene.h"

void
MoonCrawler::HealthSystem::operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, MoonCrawler::Components &components) {
    auto& health = components.get<Health>(entity->ID);


}