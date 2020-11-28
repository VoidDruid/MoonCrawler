#include "Canvas.h"
#include "Game/Render/Components/StaticSprite.h"
#include "Resources/ResourceManager.h"

using namespace MoonCrawler;

Canvas::Canvas(QWidget* Parent) :
    QSFMLCanvas(Parent), m_resourceManager{"../resources"}
{
    m_Layers.emplace_back();
}

template <class T> std::shared_ptr<T> Canvas::getResource(std::string resourceName) {
    return m_resourceManager.get<T>(resourceName);
}

void Canvas::onInit()
{
}

void Canvas::onUpdate()
{
    clear();

    static StaticSprite sprite{};
    static ResourceManager manager("../resources");
    static auto texture = getResource<Texture>("test.png");

    static float rotation = 0;

    static auto layer = Layer();

    if (rotation < 1) {
        sprite.initialize(texture, sf::Vector2i(100, 100));
        sprite.setPosition(sf::Vector2f(100, 100));
        layer.addObject(0, std::shared_ptr<IDrawable>(&sprite));
    }

    rotation += 1;
    sprite.setRotation(rotation);

    auto iter = layer.getDrawablesIterator();
    while (auto spriteOpt = iter.next()) {
        if (auto spritePtr = (*spriteOpt).lock()) {
            draw(spritePtr);
        }
    }
}

void Canvas::draw(const IDrawable& drawable) {
    sf::RenderWindow::draw(drawable.getSprite());
}

void Canvas::draw(const std::shared_ptr<IDrawable>& drawable) {
    sf::RenderWindow::draw(drawable->getSprite());
}

void Canvas::addDrawable(const std::shared_ptr<IDrawable> &drawable) {

}
