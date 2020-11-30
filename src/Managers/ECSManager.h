#pragma once

#include <vector>
#include <thread>
#include <cassert>

#include "ECS/Components.h"
#include "ECS/System.h"
#include "ECS/Entity.h"
#include "meta.h"
#include "consts.h"

namespace MoonCrawler {

#define defineAddById(T, fieldName)                                   \
void addComponent(GID entityId, T component)    {                               \
    std::lock_guard<std::mutex> lock{entityMutex};                              \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                          \
    assert(is_one_of_);                                                         \
    (*m_components).fieldName[entityId] = component;                            \
    m_Entities[entityId]->hasComponents |= has##T;                              \
}

#define defineAdd(T, fieldName)                                       \
void addComponent(const std::shared_ptr<EntityBase>& entity, T component) {     \
    std::lock_guard<std::mutex> lock{entityMutex};                              \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                          \
    assert(is_one_of_);                                                         \
    (*m_components).fieldName[entity->ID] = component;                          \
    m_Entities[entity->ID]->hasComponents |= has##T;                              \
}

#define defineRemoveById(T, fieldName)                                   \
void removeComponent(GID entityId, T component)    {                               \
    std::lock_guard<std::mutex> lock{entityMutex};                              \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                          \
    assert(is_one_of_);                                                         \
    (*m_components).fieldName.erase(entityId);                                  \
    m_Entities[entityId]->hasComponents &= ~has##T;                             \
}

#define defineRemove(T, fieldName)                                       \
void removeComponent(const std::shared_ptr<EntityBase>& entity, T component) {     \
    std::lock_guard<std::mutex> lock{entityMutex};                              \
    bool is_one_of_ = is_one_of<T, COMPONENTS>::value;                          \
    assert(is_one_of_);                                                         \
    (*m_components).fieldName.erase(entity->ID);                                  \
    m_Entities[entity->ID]->hasComponents &= ~has##T;                             \
}

class ECSManager : public std::enable_shared_from_this<ECSManager> {
public:
    ECSManager();
    void addEntity(const std::shared_ptr<EntityBase>& entity);
    void updateEntity(const std::shared_ptr<EntityBase>& entity);
    void removeEntity(GID entityId);
    void removeEntity(const std::shared_ptr<EntityBase>& entity);
    void start();

    defineAddById(Position, positions);
    defineAddById(Health, healths);

    defineAdd(Position, positions);
    defineAdd(Health, healths);

    defineRemove(Position, positions);
    defineRemove(Health, healths);

    defineRemoveById(Position, positions);
    defineRemoveById(Health, healths);

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
