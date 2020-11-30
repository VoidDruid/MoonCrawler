#pragma once

#include <unordered_map>

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
}