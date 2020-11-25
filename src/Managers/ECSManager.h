#pragma once

#include "ECS/Components.h"
#include "meta.h"

namespace MoonCrawler {
struct ECSManager {
    void registerEntity(EntityID entityId) {
        entities[entityId] = 0x0;
    }
template<typename Component>
    void addComponent(EntityID entityId, Component&& component) {
        static_assert(is_one_of<Component, Velocity, Health, Position>::value, "should be defined component!");

        if constexpr(std::is_same_v<Component, Velocity>) {
            m_components.velocities[entityId] = component;
            entities[entityId] |= hasVelocity;
        }
        if constexpr(std::is_same_v<Component, Health>) {
            m_components.healths[entityId] = component;
            entities[entityId] |= hasHealth;
        }
        if constexpr(std::is_same_v<Component, Position>) {
            m_components.positions[entityId] = component;
            entities[entityId] |= hasPosition;
        }
    }

    template<typename Component>
    void removeComponent(EntityID entityId, Component&& component) {
        static_assert(is_one_of<Component, Velocity, Health, Position>::value, "should be defined component!");

        if constexpr(std::is_same_v<Component, Velocity>) {
            m_components.velocities.erase(entityId);
            entities[entityId] &= ~hasVelocity;
        }
        if constexpr(std::is_same_v<Component, Health>) {
            m_components.healths.erase(entityId);
            entities[entityId] &= ~hasHealth;
        }
        if constexpr(std::is_same_v<Component, Position>) {
            m_components.positions.erase(entityId);
            entities[entityId] &= ~hasPosition;
        }
    }
Components m_components{};
std::unordered_map<EntityID, unsigned char> entities{};
};
}
