#include "ECSManager.h"

#include <iostream>

namespace MoonCrawler {

void ECSManager::start() {
    std::weak_ptr<ECSManager> weakSelf = shared_from_this();
    auto ecsLoop = [weakSelf]() {
        auto scenePtr = getCurrentScene();
        while(auto strongSelf = weakSelf.lock()) {
            for(auto& [_, entity] : strongSelf->m_Entities) {
                for (auto& system : strongSelf->m_Systems) {
                    unsigned char neededComponentsFlag = system->getNeededComponents();
                    bool hasComponents = (entity->hasComponents & neededComponentsFlag) == neededComponentsFlag;
                    if(hasComponents) {
                        system->operator()(scenePtr, entity, *(strongSelf->m_components));
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds (m_milSecsLoopPause));
        }
    };
    ecsThread = std::thread(ecsLoop);
    ecsThread.detach();
}

void ECSManager::removeEntity(GID entityId) {
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

#define UPDATE_COMPONENT(ComponentT) \
if(entity->has<ComponentT>()) {                            \
    m_components->add<ComponentT>(entity->ID, entity->m_components->get<ComponentT>(entity->ID)); \
}

void ECSManager::updateEntity(const std::shared_ptr<EntityBase> &entity) {
    std::lock_guard<std::mutex> lock{entityMutex};
    //m_Entities[entity->ID] = entity;

    //UPDATE_COMPONENT(Collider);
    //UPDATE_COMPONENT(Health);
   // UPDATE_COMPONENT(EnemyTrait);
   // UPDATE_COMPONENT(Transform);

    if(entity->has<Collider>()) {
        m_components->add<Collider>(entity->ID, entity->m_components->get<Collider>(entity->ID));
    }
    if(entity->has<Health>()) {
        m_components->add<Health>(entity->ID, entity->m_components->get<Health>(entity->ID));
    }
    if(entity->has<EnemyTrait>()) {
        m_components->add<EnemyTrait>(entity->ID, entity->m_components->get<EnemyTrait>(entity->ID));
    }
    if(entity->has<Transform>()) {
        m_components->add<Transform>(entity->ID, entity->m_components->get<Transform>(entity->ID));
    }
    entity->m_components = m_components;
}
}