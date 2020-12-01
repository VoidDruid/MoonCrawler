#include "StaticSprite.h"
#include "consts.h"

using namespace MoonCrawler;

void StaticSprite::setPosition(const sf::Vector2f& position) {
    m_Sprite.setPosition(position);
}

void StaticSprite::setPosition(float x, float y) {
    m_Sprite.setPosition(x , y);
}

void StaticSprite::setRotation(float angle) {
    m_Sprite.setRotation(angle);
}

void StaticSprite::setSize(const sf::Vector2i& size) {
    auto currentSize = m_Sprite.getLocalBounds();

    if (size.x == currentSize.width && size.y == currentSize.height) {
        return;
    }

    m_Sprite.setScale(
        size.x / currentSize.width,
        size.y / currentSize.height);
}

void StaticSprite::setSize(int x, int y) {
    setSize(sf::Vector2i(x, y));  // TODO
}

const sf::Sprite& MoonCrawler::StaticSprite::getSprite() const {
    return m_Sprite;
}

void StaticSprite::setTextureDirectly(const std::shared_ptr<Texture>& texture) {
    m_Sprite.setTexture(*texture);
}

void StaticSprite::setTexture(const std::shared_ptr<Texture>& texture, bool adjustSize) {
    auto adjustedScale = UNIT_VECTOR2F;

    if (adjustSize) {
        auto currentSize = m_Sprite.getLocalBounds();
        auto textureSize = texture->getSize();
        adjustedScale = sf::Vector2f(
         textureSize.x / currentSize.width,
         textureSize.y / currentSize.height);
    }

    setTextureDirectly(texture);
    center();

    // adjust size to previous value
    if (adjustSize) {
        m_Sprite.setScale(adjustedScale);
    }
}

void StaticSprite::initialize(const std::shared_ptr<Texture>& texture) {
    setTexture(texture, true);  // safe, as it is exactly what we want here
}

void StaticSprite::initialize(const std::shared_ptr<Texture>& texture, const sf::Vector2i& size) {
    setTextureDirectly(texture);
    center();
    setSize(size);
}

void StaticSprite::center() {
    // Sets sprite center at actual center of it
    auto currentSize = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(sf::Vector2f(currentSize.width / 2, currentSize.height / 2));
}

void StaticSprite::move(const sf::Vector2f& position) {
    m_Sprite.move(position);
}

void StaticSprite::rotate(float angle) {
    m_Sprite.rotate(angle);
}
