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


    template<typename T, std::enable_if<std::is_base_of<EntityBase, T>::value>>
    GID addObject(const std::shared_ptr<T>& object) {
        m_ecsManager.addEntity(object);

        if constexpr(std::is_base_of_v<IDrawable, T>) {
            m_canvas->addObject<T>(object);
        }

        return object->ID;
    }

    inline sf::Int32 getElapsedMillis();

    inline sf::Int32 getDeltaMillis();

    void start();

    sf::Vector2f getCameraPosition();

    void moveCamera(const sf::Vector2f& by);

    void setCameraPosition(const sf::Vector2f& position);

    Canvas* getCanvas();
private:
    ECSManager m_ecsManager{};

    Canvas* m_canvas;

    sf::View m_view;

    inline void updateView();
};
}
