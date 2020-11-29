#include "Canvas.h"
#include "Components/StaticSprite.h"
#include "Resources/ResourceManager.h"

using namespace MoonCrawler;

Canvas::Canvas(QWidget* Parent) :
    QSFMLCanvas(Parent), m_resourceManager{"../resources"}
{
    m_layers.emplace_back();
}

void Canvas::onInit()
{
}

void Canvas::onUpdate()
{
    clear();

    auto iter = m_layers[0].getDrawablesIterator();
    while (iter.hasValue()) {
        auto spriteWeakPtr = iter.next();
        if (auto spriteStrongPtr = spriteWeakPtr.lock()) {
            draw(spriteStrongPtr);
        }
    }
}

inline void Canvas::draw(const IDrawable& drawable) {
    sf::RenderWindow::draw(drawable.getSprite());
}

inline void Canvas::draw(const std::shared_ptr<IDrawable>& drawable) {
    sf::RenderWindow::draw(drawable->getSprite());
}

void Canvas::start() {
    m_isGoing = true;
    m_clock.restart();
    updateLastFrameTime();
}

inline void Canvas::updateLastFrameTime() {
    m_lastFrameTimeMillis = getElapsedMillis();
}

void Canvas::onAfterUpdate() {
    updateLastFrameTime();
}

void Canvas::stop() {
    m_isGoing = false;
}

void Canvas::restart() {
    stop();
    start();
}

inline sf::Int32 Canvas::getElapsedMillis() {
    return m_clock.getElapsedTime().asMilliseconds();
}

inline sf::Int32 Canvas::getDeltaMillis() {
    return getElapsedMillis() - m_lastFrameTimeMillis;
}