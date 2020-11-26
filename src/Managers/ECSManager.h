#pragma once

#include <vector>
#include <thread>
#include "ECS/Components.h"
#include "ECS/System.h"
#include "meta.h"
#include "consts.h"


namespace MoonCrawler {

#define defineAdd(T, fieldName)                              \
if constexpr(std::is_same_v<Component, T>) {                 \
    m_components.fieldName[entityId] = component;            \
    m_EntityComponentFlags[entityId] |= has##T;              \
}

#define defineRemove(T, fieldName)                           \
if constexpr(std::is_same_v<Component, T>) {                 \
    m_components.fieldName.erase(entityId);                  \
    m_EntityComponentFlags[entityId] &= ~has##T;             \
}

class ECSManager {
public:
    void registerEntity(EntityID entityId) {
        m_EntityComponentFlags[entityId] = 0x0;
    }

    void start();

    template<typename Component>
    void addComponent(EntityID entityId, Component&& component) {
        static_assert(is_one_of<Component, Position>::value, "should be defined component!");
        defineAdd(Position, positions)
    }

    template<typename Component>
    void removeComponent(EntityID entityId, Component&& component) {
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

    std::unordered_map<EntityID, unsigned char> m_EntityComponentFlags{};

    std::thread ecsThread;

    const int m_milSecsLoopPause = MILSECS_PER_FRAME_60;
};
}
