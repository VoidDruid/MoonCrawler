#pragma once

#include "Managers/ECSManager.h"
#include "Render/Canvas.h"
#include "Render/IDrawable.h"

namespace MoonCrawler {
class Scene {
public:
    explicit Scene(Canvas* canvas);

    Scene(Scene const &) = delete;
    void operator=(Scene const &x) = delete;
    Scene(Scene&&) = delete;

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
    void addComponent(const std::shared_ptr<EntityBase>& entity, Component&& component) {
        m_ecsManager->addComponent(entity, component);
    }

    template<typename Component>
    void addComponent(GID id, Component&& component) {
        m_ecsManager->addComponent(id, component);
    }

    sf::Int64 getElapsedMicros();

    sf::Int64 getDeltaMicros();

    void start();

    sf::Vector2f getCameraPosition();

    void moveCamera(const sf::Vector2f& by);

    void setCameraPosition(const sf::Vector2f& position);

    Canvas* getCanvas();
private:
    std::shared_ptr<ECSManager> m_ecsManager;

    Canvas* m_canvas;

    sf::View m_view;

    std::weak_ptr<Scene> m_currentSceneWeakPtr;

    inline void updateView();
};

std::shared_ptr<Scene> getCurrentScene();
std::shared_ptr<Scene> createScene(Canvas *canvas);
}
