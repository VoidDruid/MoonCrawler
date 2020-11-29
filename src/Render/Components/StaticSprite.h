#pragma once

#include "Render/IDrawable.h"
#include "Render/Resources/Texture.h"

namespace MoonCrawler {
class StaticSprite : public IDrawable {
public:
    StaticSprite() = default;

    StaticSprite(StaticSprite const &) = delete;
    void operator=(StaticSprite const &x) = delete;
    StaticSprite(StaticSprite&&) = delete;

    void initialize(const std::shared_ptr<Texture>& texture);

    void initialize(const std::shared_ptr<Texture>& texture, const sf::Vector2i& size);

    const sf::Sprite& getSprite() const override;

    virtual void setPosition(const sf::Vector2f& position);

    virtual void setRotation(float angle);

    virtual void setSize(const sf::Vector2i& size);

    virtual void setTexture(const std::shared_ptr<Texture>& texture, bool adjustSize);

    void setTextureDirectly(const std::shared_ptr<Texture> &texture);

    void prepare() override;

private:
    void center();

    sf::Sprite m_Sprite;
};
}

