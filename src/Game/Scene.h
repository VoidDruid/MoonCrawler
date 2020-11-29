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
        static_assert(std::is_base_of<EntityBase, T>::value, "Scene only accepts entities");
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

    template <typename T>
    void addSystem(std::shared_ptr<T>& system) {
        static_assert(std::is_base_of<System, T>::value, "Should be a derivative of System");
        m_ecsManager->addSystem(system);
    }

    template<typename Component>
    void addComponent(const std::shared_ptr<EntityBase>& entity, Component&& component) {
        m_ecsManager->addComponent(entity, component);
    }

    template<typename Component>
    void addComponent(GID id, Component&& component) {
        m_ecsManager->addComponent(id, component);
    }

    inline sf::Int32 getElapsedMillis();

    inline sf::Int32 getDeltaMillis();

    void start();

    sf::Vector2f getCameraPosition();

    void moveCamera(const sf::Vector2f& by);

    void setCameraPosition(const sf::Vector2f& position);

    Canvas* getCanvas();
private:
    std::shared_ptr<ECSManager> m_ecsManager;

    Canvas* m_canvas;

    sf::View m_view;

    inline void updateView();
};
}
