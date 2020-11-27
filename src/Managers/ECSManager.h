#pragma once

#include <vector>
#include <thread>

#include "ECS/Components.h"
#include "ECS/System.h"
#include "ECS/Entity.h"
#include "meta.h"
#include "consts.h"

namespace MoonCrawler {

#define defineAdd(T, fieldName)                              \
if constexpr(std::is_same_v<Component, T>) {                 \
    m_components.fieldName[entityId] = component;            \
    m_Entities[entityId]->components |= has##T;              \
}

#define defineRemove(T, fieldName)                           \
if constexpr(std::is_same_v<Component, T>) {                 \
    m_components.fieldName.erase(entityId);                  \
    m_Entities[entityId]->components &= ~has##T;             \
}

class ECSManager {
public:
    void addEntity(const std::shared_ptr<Entity>& entity);
    void removeEntity(EntityID entityId);
    void start();

    template<typename Component>
    void addComponent(EntityID entityId, Component&& component) {
        std::lock_guard<std::mutex> lock{entityMutex};
        static_assert(is_one_of<Component, Position>::value, "should be defined component!");
        defineAdd(Position, positions)
    }

    template<typename Component>
    void removeComponent(EntityID entityId, Component&& component) {
        std::lock_guard<std::mutex> lock{entityMutex};
        static_assert(is_one_of<Component, Position>::value, "should be defined component!");
        defineRemove(Position, positions)
    }

    template<typename SystemT>
    void addSystem() {
        m_Systems.push_back(std::move(std::make_shared<SystemT>()));
    }
private:
    void ecsLoop();

    std::vector<std::shared_ptr<System>> m_Systems{};
    Components m_components{};
    std::unordered_map<EntityID, std::shared_ptr<Entity>> m_Entities{};
    std::thread ecsThread;
    const int m_milSecsLoopPause = MILSECS_PER_FRAME_60;
    std::mutex entityMutex{};
};
}
