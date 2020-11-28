#pragma once

#include <vector>
#include <thread>

#include "ECS/Components.h"
#include "ECS/System.h"
#include "ECS/Entity.h"
#include "meta.h"
#include "consts.h"

namespace MoonCrawler {

#define defineAdd(T, fieldName, entityId)                       \
if constexpr(std::is_same_v<Component, T>) {                    \
    (*m_components).fieldName[entityId] = component;            \
    m_Entities[entityId]->hasComponents |= has##T;              \
}

#define defineRemove(T, fieldName, entityId)                    \
if constexpr(std::is_same_v<Component, T>) {                    \
    (*m_components).fieldName.erase(entityId);                  \
    m_Entities[entityId]->hasComponents &= ~has##T;             \
}

class ECSManager : public std::enable_shared_from_this<ECSManager> {
public:
    ECSManager();
    void addEntity(const std::shared_ptr<EntityBase>& entity);
    void removeEntity(EntityID entityId);
    void removeEntity(const std::shared_ptr<EntityBase>& entity);
    void start();

    template<typename Component>
    void addComponent(EntityID entityId, Component&& component) {
        std::lock_guard<std::mutex> lock{entityMutex};
        static_assert(is_one_of<Component, COMPONENTS>::value, "should be defined component!");
        defineAdd(Position, positions, entityId);
        defineAdd(Health, healths, entityId);
    }

    template<typename Component>
    void addComponent(const std::shared_ptr<EntityBase>& entity, Component&& component) {
        std::lock_guard<std::mutex> lock{entityMutex};
        static_assert(is_one_of<Component, COMPONENTS>::value, "should be defined component!");
        defineAdd(Position, positions, entity->ID);
        defineAdd(Health, healths, entity->ID);
    }

    template<typename Component>
    void removeComponent(EntityID entityId, Component&& component) {
        std::lock_guard<std::mutex> lock{entityMutex};
        static_assert(is_one_of<Component, COMPONENTS>::value, "should be defined component!");
        defineRemove(Position, positions, entityId);
        defineRemove(Health, healths, entityId);
    }

    template<typename Component>
    void removeComponent(const std::shared_ptr<EntityBase>& entity, Component&& component) {
        std::lock_guard<std::mutex> lock{entityMutex};
        static_assert(is_one_of<Component, COMPONENTS>::value, "should be defined component!");
        defineRemove(Position, positions, entity->ID);
        defineRemove(Health, healths, entity->ID);
    }

    template<typename SystemT>
    void addSystem() {
        m_Systems.push_back(std::move(std::make_shared<SystemT>()));
    }
private:
    std::vector<std::shared_ptr<System>> m_Systems{};
    std::shared_ptr<Components> m_components{};
    std::unordered_map<EntityID, std::shared_ptr<EntityBase>> m_Entities{};
    std::thread ecsThread;
    static constexpr int m_milSecsLoopPause = MILSECS_PER_FRAME_60;
    std::mutex entityMutex{};
};
}
