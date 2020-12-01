#pragma once

#include <unordered_map>
#include <nlohmann/json.hpp>

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
inline TO_JSON_1(Collider, isBlocking);
inline FROM_JSON_1(Collider, isBlocking);
inline TO_JSON_2(Health, max, current);
inline FROM_JSON_2(Health, max, current);

#define COMPONENTS Transform, Collider, EnemyTrait, Health
}