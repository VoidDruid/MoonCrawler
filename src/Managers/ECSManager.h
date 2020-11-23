#pragma once

#include "ECS/Components.h"
#include "meta.h"

namespace MoonCrawler {
struct ECSManager {
template<typename Component>
    void addComponent(EntityID entityId, Component&& component) {
        static_assert(is_one_of<Component, Velocity, Health, Position>::value, "should be defined component!");

        if constexpr(std::is_same_v<Component, Velocity>) {
            m_components.velocities[entityId] = component;
        }
        if constexpr(std::is_same_v<Component, Health>) {
            m_components.healths[entityId] = component;
        }
        if constexpr(std::is_same_v<Component, Position>) {
            m_components.positions[entityId] = component;
        }
    }

    template<typename Component>
    void removeComponent(EntityID entityId, Component&& component) {
        static_assert(is_one_of<Component, Velocity, Health, Position>::value, "should be defined component!");

        if constexpr(std::is_same_v<Component, Velocity>) {
            m_components.velocities.erase(entityId);
        }
        if constexpr(std::is_same_v<Component, Health>) {
            m_components.healths.erase(entityId);
        }
        if constexpr(std::is_same_v<Component, Position>) {
            m_components.positions.erase(entityId);
        }
    }
Components m_components{};
};
}
