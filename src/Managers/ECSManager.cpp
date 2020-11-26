#include "ECSManager.h"

using namespace MoonCrawler;

void ECSManager::ecsLoop() {
    while(true) {
        for(auto& [id, entity] : m_Entities) {
            for (auto& system : m_Systems) {
                unsigned char neededComponentsFlag = system->getNeededComponents();
                bool hasComponents = (entity->components & neededComponentsFlag) == neededComponentsFlag;
                if(hasComponents) {
                    system->operator()(id, m_components);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (m_milSecsLoopPause));
    }
}

void ECSManager::start() {
    ecsThread = std::thread(&ECSManager::ecsLoop, this);
    ecsThread.detach();
}

void ECSManager::removeEntity(EntityID entityId) {
    std::lock_guard<std::mutex> lock{entityMutex};
    m_Entities.erase(entityId);
}

void ECSManager::addEntity(const std::shared_ptr<Entity>& entity) {
    std::lock_guard<std::mutex> lock{entityMutex};
    entity->ID = generateId();
    m_Entities[entity->ID] = entity;
}