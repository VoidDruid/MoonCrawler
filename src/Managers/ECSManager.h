#pragma once

#include <vector>
#include <thread>
#include <cassert>

#include "ECS/Components.h"
#include "ECS/System.h"
#include "ECS/Entity.h"
#include "meta.h"
#include "consts.h"
#include "Utils/MappedIterator.hpp"

namespace MoonCrawler {

#define __RegisterMethods__(T)                                                         \
void addComponent(const std::shared_ptr<EntityBase>& entity, const T& component) {     \
    std::lock_guard<std::mutex> lock{entityMutex};                                     \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                                 \
    assert(is_one_of_);                                                                \
    m_components->add<T>(entity->ID, component);                                       \
    m_Entities[entity->ID]->hasComponents |= has##T;                                   \
}                                                                                      \
void addComponent(GID entityId, const T& component) {                                  \
    std::lock_guard<std::mutex> lock{entityMutex};                                     \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                                 \
    assert(is_one_of_);                                                                \
    m_components->add<T>(entityId, component);                                         \
    m_Entities[entityId]->hasComponents |= has##T;                                     \
}                                                                                      \
void removeComponent(GID entityId, T component)    {                                   \
    std::lock_guard<std::mutex> lock{entityMutex};                                     \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                                 \
    assert(is_one_of_);                                                                \
    m_components->remove<T>(entityId);                                                 \
    m_Entities[entityId]->hasComponents &= ~has##T;                                    \
}                                                                                      \
void removeComponent(const std::shared_ptr<EntityBase>& entity, T component) {         \
    std::lock_guard<std::mutex> lock{entityMutex};                                     \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                                 \
    assert(is_one_of_);                                                                \
    m_components->remove<T>(entity->ID);                                               \
    m_Entities[entity->ID]->hasComponents &= ~has##T;                                  \
}

class ECSManager : public std::enable_shared_from_this<ECSManager> {
public:
    ECSManager();
    void addEntity(const std::shared_ptr<EntityBase>& entity);
    void updateEntity(const std::shared_ptr<EntityBase>& entity);
    void removeEntity(GID entityId);
    void removeEntity(const std::shared_ptr<EntityBase>& entity);
    void start();

    __RegisterMethods__(Transform);
    __RegisterMethods__(Collider);
    __RegisterMethods__(Health);
    __RegisterMethods__(EnemyTrait);
    __RegisterMethods__(MeleeAttack);
    __RegisterMethods__(RangedAttack);
    __RegisterMethods__(PlayerTrait);

    template<typename SystemT, typename ...Args>
    void addSystem(Args... args) {
        m_Systems.push_back(std::move(std::make_shared<SystemT>(args...)));
    }

    void addSystem(std::shared_ptr<System> system) {
        m_Systems.push_back(std::move(system));
    }

    void addSystem(const std::shared_ptr<System>& system) {
        m_Systems.push_back(system);
    }

    template <typename... Args>
    struct ComponentFlag;

    template <>
    struct ComponentFlag<> {
        static constexpr unsigned char value = 0x0;
    };

    template <typename First, typename... Args>
    struct ComponentFlag<First, Args...> {
        static constexpr unsigned char value = getBitFlag<First>() | ComponentFlag<Args...>::value;
    };

    template<typename... Args>
    MappedIterator<std::unordered_map<GID, std::shared_ptr<EntityBase>>, GID> getFitting() {
        constexpr unsigned char neededFlags = ComponentFlag<Args...>::value;

        return MappedIterator<std::unordered_map<GID, std::shared_ptr<EntityBase>>, GID>(
            m_Entities,
            [neededFlags, this](const std::pair<GID, std::shared_ptr<EntityBase>>& key_value) -> std::optional<GID> {
                std::lock_guard<std::mutex> lock{entityMutex};
                bool hasComponents = (key_value.second->hasComponents & neededFlags) == neededFlags;
                if (hasComponents) {
                    return key_value.first;
                }
                return std::nullopt;
            });
    }

private:
    std::vector<std::shared_ptr<System>> m_Systems{};

    std::shared_ptr<Components> m_components{};

    std::unordered_map<GID, std::shared_ptr<EntityBase>> m_Entities{};

    std::thread ecsThread;

    static constexpr int m_milSecsLoopPause = MILSECS_PER_FRAME_60;

    std::mutex entityMutex{};
};
std::shared_ptr<Scene> getCurrentScene();
}
