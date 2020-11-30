#pragma once

#include <unordered_map>
#include <nlohmann/json.hpp>

#include "Common.h"

namespace MoonCrawler {

template <typename Type>
using ComponentMap = std::unordered_map<GID, Type>;

template <typename C>
constexpr unsigned char getBitFlag();

#define __ComponentDef__(T, bitFlag)                                  \
constexpr unsigned char has##T = bitFlag;                             \
struct T;                                                             \
template <> constexpr unsigned char getBitFlag<T>() {return bitFlag;} \
using T##s = ComponentMap<T>;                                         \
struct T

#define __ComponentGetter__(T, field) \
template<> T& get<T>(GID id) { return field[id]; }

__ComponentDef__(Position, 0x01) {  // TODO: automate (in macro) flag increment
    float x;
    float y;
};

__ComponentDef__(Health, 0x02) {  // TODO: automate (in macro) flag increment
    float value;
};

constexpr unsigned char isKeyboardPlayable = 0x04;

struct Components
{
    Positions positions;
    Healths healths;

    template <typename T>
    T& get(GID id);

    __ComponentGetter__(Position, positions);
    __ComponentGetter__(Health, healths);
};
#define COMPONENTS Position, Health

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

inline TO_JSON_2(Position, x, y);
inline TO_JSON_1(Health, value);
inline FROM_JSON_2(Position, x, y);
inline FROM_JSON_1(Health, value);
}