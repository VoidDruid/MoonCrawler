#pragma once

#include <unordered_map>

#include "Common.h"

namespace MoonCrawler {

template <typename Type>
using ComponentMap = std::unordered_map<GID, Type>;

template <typename C>
constexpr unsigned char getBitFlag();

#define Component(T, bitFlag)                                         \
constexpr unsigned char has##T = bitFlag;                             \
struct T;                                                             \
template <> constexpr unsigned char getBitFlag<T>() {return bitFlag;} \
using T##s = ComponentMap<T>;                                         \
struct T

Component(Position, 0x01) {  // TODO: automate (in macro) flag increment
    float x;
    float y;
};

Component(Health, 0x02) {  // TODO: automate (in macro) flag increment
    float value;
};

struct Components
{
    Positions positions;
    Healths healths;
};
#define COMPONENTS Position, Health
}