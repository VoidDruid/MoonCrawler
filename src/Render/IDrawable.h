#pragma once

#include <SFML/Graphics.hpp>

namespace MoonCrawler {

class Scene;

class IDrawable {
public :
    [[nodiscard]] virtual const sf::Sprite& getSprite() const = 0;
    virtual void prepare(const std::shared_ptr<Scene>& scene) = 0;
};
}
