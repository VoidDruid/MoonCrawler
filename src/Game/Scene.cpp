#include "Scene.h"

using namespace MoonCrawler;

Scene::Scene(Canvas *canvas) :
    m_canvas{canvas}
{
    m_view = sf::View(sf::Vector2f(0,0), m_canvas->getDefaultView().getSize());
    m_canvas->setView(m_view);
    m_ecsManager = std::make_shared<ECSManager>();
}

sf::Int64 Scene::getElapsedMicros() {
    return m_canvas->getElapsedMicros();
}

sf::Int64 Scene::getDeltaMicros() {
    return m_canvas->getDeltaMicros();
}

void Scene::start() {
    m_currentSceneWeakPtr = getCurrentScene();
    auto scenePtr = m_currentSceneWeakPtr.lock();
    if (!scenePtr) {
        return;
    }
    m_canvas->start();
    m_ecsManager->start();
}

sf::Vector2f Scene::getCameraPosition() {
    return m_view.getCenter();
}


void Scene::moveCamera(const sf::Vector2f& by) {
    m_view.move(by);
    updateView();
}

void Scene::setCameraPosition(const sf::Vector2f& position) {
    m_view.setCenter(position);
    updateView();
}

Canvas* Scene::getCanvas() {
    return m_canvas;
}

inline void Scene::updateView() {
    m_canvas->setView(m_view);
}

namespace MoonCrawler {
    static std::shared_ptr<Scene> _currentScene = nullptr;

    std::shared_ptr<Scene> getCurrentScene() {
        return _currentScene;
    }

    std::shared_ptr<Scene> createScene(Canvas *canvas) {
        _currentScene = std::make_shared<Scene>(canvas);
        return _currentScene;
    }
}

