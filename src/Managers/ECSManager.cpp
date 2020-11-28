#include "ECSManager.h"

#include <iostream>

namespace MoonCrawler {

void ECSManager::start() {
    std::weak_ptr<ECSManager> weakSelf = shared_from_this();
    auto ecsLoop = [weakSelf]() {
        while(auto strongSelf = weakSelf.lock()) {
            for(auto& [id, entity] : strongSelf->m_Entities) {
                for (auto& system : strongSelf->m_Systems) {
                    unsigned char neededComponentsFlag = system->getNeededComponents();
                    bool hasComponents = (entity->hasComponents & neededComponentsFlag) == neededComponentsFlag;
                    if(hasComponents) {
                        system->operator()(id, *(strongSelf->m_components));
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds (m_milSecsLoopPause));
        }
    };
    ecsThread = std::thread(ecsLoop);
    ecsThread.detach();
}

void ECSManager::removeEntity(EntityID entityId) {
    std::lock_guard<std::mutex> lock{entityMutex};
    m_Entities.erase(entityId);
}

void ECSManager::removeEntity(const std::shared_ptr<EntityBase>& entity) {
    std::lock_guard<std::mutex> lock{entityMutex};
    m_Entities.erase(entity->ID);
}

void ECSManager::addEntity(const std::shared_ptr<EntityBase>& entity) {
    std::lock_guard<std::mutex> lock{entityMutex};
    entity->ID = generateId();
    entity->m_components = m_components;
    m_Entities[entity->ID] = entity;
}

ECSManager::ECSManager()
    : m_components{std::make_shared<Components>()}
    {}
}