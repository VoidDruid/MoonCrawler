#pragma once

#include "Managers/ECSManager.h"
#include "Render/Canvas.h"
#include "Render/IDrawable.h"

namespace MoonCrawler {
class Scene : public std::enable_shared_from_this<Scene>{
public:
    explicit Scene(Canvas* canvas);

    Scene(Scene const &) = delete;
    void operator=(Scene const &x) = delete;
    Scene(Scene&&) = delete;

    void updateEntity(const std::shared_ptr<EntityBase>& entity);

    template<typename T>
    GID addObject(const std::shared_ptr<T>& object) {
        m_ecsManager->addEntity(object);

        if constexpr(std::is_base_of_v<IDrawable, T>) {
            m_canvas->addObject<T>(object);
        }

        return object->ID;
    }

    template <typename T, typename ...Args>
    void addSystem(Args... args) {
        static_assert(std::is_base_of<System, T>::value, "Should be a derivative of System");
        m_ecsManager->addSystem<T>(std::forward<Args>(args)...);
    }

    template<typename Component>
    void addComponent(const std::shared_ptr<EntityBase>& entity, const Component& component) {
        m_ecsManager->addComponent(entity, component);
    }

    template<typename Component>
    void addComponent(GID id, Component&& component) {
        m_ecsManager->addComponent(id, component);
    }

    template <class T>
    std::shared_ptr<T> getResource(std::string resourceName) {
        return m_canvas->getResource<T>(resourceName);
    }
    void startECSManager();

    sf::Int64 getElapsedMicros();

    sf::Int64 getDeltaMicros();

    void start();

    sf::Vector2f getCameraPosition();

    void moveCamera(const sf::Vector2f& by);

    void setCameraPosition(const sf::Vector2f& position);

    Canvas* getCanvas();

    void populate(const std::string& layoutName);

    template<typename... T>
    MappedIterator<std::unordered_map<GID, std::shared_ptr<EntityBase>>, GID> getFitting() {
        return m_ecsManager->getFitting<T...>();
    }
private:
    std::shared_ptr<ECSManager> m_ecsManager;

    Canvas* m_canvas;

    sf::View m_view;

    std::weak_ptr<Scene> m_currentSceneWeakPtr;

    bool m_isPopulated{false};

    inline void updateView();
};

std::shared_ptr<Scene> getCurrentScene();
std::shared_ptr<Scene> createScene(Canvas *canvas);
}
