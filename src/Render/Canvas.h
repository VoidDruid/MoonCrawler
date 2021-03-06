#pragma once

#include "UI/QSFMLCanvas.h"
#include "Resources/ResourceManager.h"
#include "IDrawable.h"
#include "Layer.h"

namespace MoonCrawler {
class Canvas : public QSFMLCanvas {
public :
    explicit Canvas(QWidget* Parent);

    Canvas(Canvas const &) = delete;
    void operator=(Canvas const &x) = delete;
    Canvas(Canvas&&) = delete;

    inline void draw(const IDrawable& drawable);

    inline void draw(const std::shared_ptr<IDrawable>& drawable);

    template <class T>
    std::shared_ptr<T> getResource(std::string resourceName) {
        return m_resourceManager.get<T>(resourceName);
    }

    template <typename T>
    GID addObject(const std::shared_ptr<T>& object) {
        return m_layers[0].addObject<T>(object);
    }

    void removeObject(GID objectId);

    void start();

    void stop();

    void restart();

    sf::Int64 getElapsedMicros();

    sf::Int64 getDeltaMicros();
private :
    void onInit() override;

    void onUpdate() override;

    void onAfterUpdate() override;

    inline void updateLastFrameTime();

    ResourceManager m_resourceManager;

    std::vector<Layer> m_layers{};

    sf::Clock m_clock{};

    sf::Int64 m_lastFrameTimeMicros{0};

    bool m_isGoing{false};
};

class Scene;
std::shared_ptr<Scene> getCurrentScene();
}