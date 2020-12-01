#include "ECSManager.h"
#include "Managers/NetworkManager.h"

#include <iostream>

namespace MoonCrawler {

void sendToDeleteEvent(std::vector<GID>& toDelete) {
    auto networkManager = getNetworkManager();
    nlohmann::json toDeleteJson = nlohmann::json{};
    toDeleteJson["toDelete"] = nlohmann::json::array();
    toDeleteJson["gameState"] = "inGame";

    for(auto& gid : toDelete) {
        toDeleteJson["toDelete"].push_back(gid);
    }
    Event event{
            toDeleteJson,
            EventType::GameEvent,
            EventStatus::New
    };
    networkManager->sendEvent(event);
}
void ECSManager::start() {
    std::weak_ptr<ECSManager> weakSelf = shared_from_this();
    auto ecsLoop = [weakSelf]() {
        auto scenePtr = getCurrentScene();
        while(auto strongSelf = weakSelf.lock()) {

            if(not strongSelf->m_toDelete.empty()) {
                sendToDeleteEvent(strongSelf->m_toDelete);
            }

            for (GID toDelete : strongSelf->m_toDelete) {
                strongSelf->m_Entities.erase(toDelete);
            }
            strongSelf->m_toDelete.clear();
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
    m_toDelete.push_back(entityId);
}

void ECSManager::removeEntity(const std::shared_ptr<EntityBase>& entity) {
    std::lock_guard<std::mutex> lock{entityMutex};
    m_toDelete.push_back(entity->ID);
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

    UPDATE_COMPONENT(Collider);
    UPDATE_COMPONENT(Health);
    UPDATE_COMPONENT(EnemyTrait);
    UPDATE_COMPONENT(Transform);
    UPDATE_COMPONENT(MeleeAttack);
    UPDATE_COMPONENT(RangedAttack);
    UPDATE_COMPONENT(PlayerTrait);

    entity->m_components = m_components;
}
}