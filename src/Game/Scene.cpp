#include "Scene.h"

#include "Managers/GameManager.h"

using namespace MoonCrawler;

Scene::Scene(Canvas *canvas) :
    m_canvas{canvas}
{
    m_view = sf::View(sf::Vector2f(0,0), m_canvas->getDefaultView().getSize());
    m_canvas->setView(m_view);
    m_ecsManager = std::make_shared<ECSManager>();
}

void Scene::updateEntity(const std::shared_ptr<EntityBase>& entity) {
    m_ecsManager->updateEntity(entity);
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

void Scene::startECSManager() {
    //m_ecsManager->start();
}
sf::Vector2f Scene::getCameraPosition() {
    auto& center = m_view.getCenter();
    return sf::Vector2f{center.x / PIXELS_PER_UNIT, -center.y / PIXELS_PER_UNIT};
}


void Scene::moveCamera(const sf::Vector2f& by) {
    m_view.move(by.x * PIXELS_PER_UNIT, -by.y * PIXELS_PER_UNIT);
    updateView();
}

void Scene::setCameraPosition(const sf::Vector2f& position) {
    m_view.setCenter(position.x * PIXELS_PER_UNIT, -position.y * PIXELS_PER_UNIT);
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

