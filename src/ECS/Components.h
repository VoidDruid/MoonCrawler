#pragma once

#include <unordered_map>
#include <nlohmann/json.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

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

inline sf::Rect<float> toRect(const Transform& transform) {
    return sf::Rect<float>{
            transform.position.x - transform.size.x / 2,
            transform.position.y - transform.size.y / 2,
            float(transform.size.x),
            float(transform.size.y),
    };
}

__ComponentDef__(Collider, 1 << 1) {
    bool isBlocking{false};
};

__ComponentDef__(EnemyTrait, 1 << 2) {};

__ComponentDef__(MeleeAttack, 1 << 3) {
    int damage{10};
    float rechargeTimeSecs{1};
    sf::Int64 _lastStrikeMicros{0};
};

__ComponentDef__(RangedAttack, 1 << 4) : public MeleeAttack {};

__ComponentDef__(Health, 1 << 5) {
    int max{100};
    int current{100};
};

__ComponentDef__(PlayerTrait, 1 << 6) {};

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
    __RegisterComponent__(PlayerTrait);
};

#define COMPONENTS Transform, Collider, EnemyTrait, Health, MeleeAttack, RangedAttack, PlayerTrait

#define TO_JSON_1(COMPONENT, field_1) \
void to_json(nlohmann::json& j, const COMPONENT& c) { \
    j = nlohmann::json{{#field_1, c.field_1}}; \
}

#define TO_JSON_2(COMPONENT, field_1, field_2) \
void to_json(nlohmann::json& j, const COMPONENT& c) { \
    j = nlohmann::json{{#field_1, c.field_1}, {#field_2, c.field_2}}; \
}

#define FROM_JSON_1(COMPONENT, field_1) \
void from_json(const nlohmann::json& j, COMPONENT& c) { \
    j.at(#field_1).get_to(c.field_1);\
}

#define FROM_JSON_2(COMPONENT, field_1, field_2) \
void from_json(const nlohmann::json& j, COMPONENT& c) { \
    j.at(#field_1).get_to(c.field_1);\
    j.at(#field_2).get_to(c.field_2);\
}

inline void to_json(nlohmann::json& j, const Transform& c) {
    j = nlohmann::json{
        {"x", c.size.x},
        {"y", c.size.y},
        {"width", c.position.x},
        {"height", c.position.y},
    };
}

inline void from_json(const nlohmann::json& j, Transform& c) {
    j.at("x").get_to(c.size.x);
    j.at("y").get_to(c.size.y);
    j.at("width").get_to(c.position.x);
    j.at("height").get_to(c.position.y);
}

inline void to_json(nlohmann::json& j, const EnemyTrait& c) {
    j = nlohmann::json{};
}

inline void from_json(const nlohmann::json& j, EnemyTrait& c) {
    c = EnemyTrait{};
}

inline void to_json(nlohmann::json& j, const PlayerTrait& c) {
    j = nlohmann::json{};
}

inline void from_json(const nlohmann::json& j, PlayerTrait& c) {
    c = PlayerTrait{};
}

inline void to_json(nlohmann::json& j, const MeleeAttack& c) {
    j = nlohmann::json{
        {"damage", c.damage},
        {"rechargeTimeSecs", c.rechargeTimeSecs},
        {"_lastStrikeMicros", c._lastStrikeMicros},
    };
}

inline void from_json(const nlohmann::json& j, MeleeAttack& c) {
    j.at("damage").get_to(c.damage);
    j.at("rechargeTimeSecs").get_to(c.rechargeTimeSecs);
    j.at("_lastStrikeMicros").get_to(c._lastStrikeMicros);
}

inline TO_JSON_1(Collider, isBlocking);
inline FROM_JSON_1(Collider, isBlocking);
inline TO_JSON_2(Health, max, current);
inline FROM_JSON_2(Health, max, current);
}