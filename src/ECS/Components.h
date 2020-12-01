#pragma once

#include <unordered_map>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Common.h"

namespace MoonCrawler {

template <typename Type> using ComponentMap = std::unordered_map<GID, Type>;
template <typename C> constexpr unsigned char getBitFlag();

#define __ComponentDef__(T, bitFlag)                                  \
constexpr unsigned char has##T = bitFlag;                             \
struct T;                                                             \
template <> constexpr unsigned char getBitFlag<T>() {return has##T;}  \
using T##s = ComponentMap<T>;                                         \
struct T

#define __RegisterComponent__(T)                                        \
T##s T##Store;                                                          \
template<> inline T& get<T>(GID id) { return T##Store[id]; }            \
template<> inline void remove<T>(GID id) { T##Store.erase(id); }        \
template<> inline void add<T>(GID id, const T& component) {             \
    T##Store[id] = std::move(component);                                \
}                                                                       \

__ComponentDef__(Transform, 0x01) {  // TODO: automate (in macro) flag increment
    sf::Vector2f position;
    sf::Vector2i size;

    Transform() : position{}, size{} {};
    Transform(const sf::Vector2f& position) : position{position}, size{} {};
    Transform(const sf::Vector2f& position, const sf::Vector2i& size) : position{position}, size{size} {};
    Transform(float x, float y, int width, int height) : position{x, y}, size{width, height} {};
};

__ComponentDef__(Collider, 0x02) {
    bool isBlocking{false};
};

__ComponentDef__(EnemyTrait, 0x04) {
};

__ComponentDef__(Health, 0x08) {
    int max{100};
    int current{100};
};

struct Components
{
    template <typename T> inline T& get(GID id);
    template <typename T> inline void remove(GID id);
    template <typename T> inline void add(GID id, const T& component);

    __RegisterComponent__(Transform);
    __RegisterComponent__(Collider);
    __RegisterComponent__(EnemyTrait);
    __RegisterComponent__(Health);
};

#define COMPONENTS Transform, Collider, EnemyTrait, Health
}