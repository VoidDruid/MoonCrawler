#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <nlohmann/json.hpp>

namespace MoonCrawler {
struct Wall {
    sf::Vector2f position;
    sf::Vector2i size;

    Wall() : position{}, size{} {};
    Wall(const sf::Vector2f& position, const sf::Vector2i& size) : position{position}, size{size} {};
    Wall(float x, float y, int width, int height) : position{x, y}, size{width, height} {};
};

struct Layout {
    explicit Layout(const nlohmann::json& layoutData) {
        auto& wallsData = layoutData["layout"]["walls"];
        walls.reserve(wallsData.size());

        for (auto& wallData : wallsData) {
            walls.emplace_back(wallData["x"], wallData["y"], wallData["width"], wallData["height"]);
        }
    }

    Layout(Layout const &) = delete;
    void operator=(Layout const &x) = delete;
    Layout(Layout&&) = delete;

    std::vector<Wall> walls{};
};
}