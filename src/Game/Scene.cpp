#include "Scene.h"

using namespace MoonCrawler;

Scene::Scene(MoonCrawler::Canvas *canvas) :
    m_canvas{canvas}
{
    m_view = sf::View(sf::Vector2f(0,0), m_canvas->getDefaultView().getSize());
    m_canvas->setView(m_view);
}

sf::Int32 Scene::getElapsedMillis() {
    return m_canvas->getElapsedMillis();
}

sf::Int32 Scene::getDeltaMillis() {
    return m_canvas->getDeltaMillis();
}

void Scene::start() {
    m_canvas->start();
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