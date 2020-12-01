#pragma once

#include "SFML/Graphics.hpp"

namespace MoonCrawler {
constexpr int PIXELS_PER_UNIT = 10;

constexpr int MILSECS_PER_FRAME_60 = 1000 / 150;

const sf::Vector2f UNIT_VECTOR2F = sf::Vector2f(1, 1);

const std::string TEST_TEXTURE_NAME = "test.png";

template<typename T, typename V>
sf::Vector2<T> operator* (const sf::Vector2<T>& vec, V m) {
    return std::move(sf::Vector2<T>{vec.x * m, vec.y * m});
}

template<typename T, typename V>
sf::Vector2<T> operator* (V m, const sf::Vector2<T>& vec) {
    return std::move(sf::Vector2<T>{vec.x * m, vec.y * m});
}

template<typename T, typename V>
sf::Vector2<T> operator/ (const sf::Vector2<T>& vec, V m) {
    return std::move(sf::Vector2<T>{vec.x / m, vec.y / m});
}

template<typename T, typename V>
sf::Vector2<T> operator/ (V m, const sf::Vector2<T>& vec) {
    return std::move(sf::Vector2<T>{vec.x / m, vec.y / m});
}


}