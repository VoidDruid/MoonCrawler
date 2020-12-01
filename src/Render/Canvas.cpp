#include "Canvas.h"
#include "Components/StaticSprite.h"

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
    auto currentScenePtr = getCurrentScene();
    while (iter.hasValue()) {
        auto drawableWeakPtr = iter.next();
        if (auto drawableStrongPtr = drawableWeakPtr.lock()) {
            drawableStrongPtr->prepare(currentScenePtr);
            draw(drawableStrongPtr);
        }
    }
}

void Canvas::draw(const IDrawable& drawable) {
    sf::RenderWindow::draw(drawable.getSprite());
}

void Canvas::draw(const std::shared_ptr<IDrawable>& drawable) {
    sf::RenderWindow::draw(drawable->getSprite());
}

void Canvas::start() {
    m_isGoing = true;
    m_clock.restart();
    updateLastFrameTime();
}

inline void Canvas::updateLastFrameTime() {
    m_lastFrameTimeMicros = getElapsedMicros();
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

sf::Int64 Canvas::getElapsedMicros() {
    return m_clock.getElapsedTime().asMicroseconds();
}

sf::Int64 Canvas::getDeltaMicros() {
    return getElapsedMicros() - m_lastFrameTimeMicros;
}

void Canvas::removeObject(GID objectId) {
    m_layers[0].removeObject(objectId);
}
