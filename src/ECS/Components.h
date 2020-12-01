#pragma once

#include <unordered_map>

#include "SFML/System.hpp"
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

__ComponentDef__(Transform, 1 << 0) {  // TODO: automate (in macro) flag increment
    sf::Vector2f position;
    sf::Vector2i size;

    Transform() : position{}, size{} {};
    Transform(const sf::Vector2f& position) : position{position}, size{} {};
    Transform(const sf::Vector2f& position, const sf::Vector2i& size) : position{position}, size{size} {};
    Transform(float x, float y, int width, int height) : position{x, y}, size{width, height} {};
};

__ComponentDef__(Collider, 1 << 1) {
    bool isBlocking{false};
};

__ComponentDef__(EnemyTrait, 1 << 2) {};

__ComponentDef__(MeleeAttack, 1 << 3) {
    int damage{10};
    float rechargeTimeSecs{1};
    sf::Int64 _lastStrikeMicros{0};
};

__ComponentDef__(RangedAttack, 1 << 4) {
    int damage{5};
    float rechargeTimeSecs{1};
    sf::Int64 _lastStrikeMicros{0};
};

__ComponentDef__(Health, 1 << 5) {
    int max{100};
    int current{100};
};

inline sf::Rect<float> toRect(const Transform& transform) {
    return sf::Rect<float>{
        transform.position.x - transform.size.x / 2,
        transform.position.y - transform.size.y / 2,
        float(transform.size.x),
        float(transform.size.y),
    };
}

struct Components
{
    template <typename T> inline T& get(GID id);
    template <typename T> inline void remove(GID id);
    template <typename T> inline void add(GID id, const T& component);

    __RegisterComponent__(Transform);
    __RegisterComponent__(Collider);
    __RegisterComponent__(EnemyTrait);
    __RegisterComponent__(Health);
    __RegisterComponent__(MeleeAttack);
    __RegisterComponent__(RangedAttack);
};

#define COMPONENTS Transform, Collider, EnemyTrait, Health, MeleeAttack, RangedAttack
}