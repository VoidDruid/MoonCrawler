#pragma once

#include <SFML/Graphics.hpp>

namespace MoonCrawler {
class IDrawable {
public :
    [[nodiscard]] virtual const sf::Sprite& getSprite() const = 0;
    virtual void prepare() = 0;
};
}
