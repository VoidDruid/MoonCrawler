#pragma once

#include <unordered_map>

#include "Common.h"

namespace MoonCrawler {

template <typename Type>
using ComponentMap = std::unordered_map<GID, Type>;

template <typename C>
constexpr unsigned char getBitFlag();

#define DefineComponent(T, bitFlag)                                         \
constexpr unsigned char has##T = bitFlag;                             \
struct T;                                                             \
template <> constexpr unsigned char getBitFlag<T>() {return bitFlag;} \
using T##s = ComponentMap<T>;                                         \
struct T

DefineComponent(Position, 0x01) {  // TODO: automate (in macro) flag increment
    float x;
    float y;
};

DefineComponent(Health, 0x02) {  // TODO: automate (in macro) flag increment
    float value;
};

constexpr unsigned char isKeyboardPlayable = 0x04;

struct Components
{
    Positions positions;
    Healths healths;
};
#define COMPONENTS Position, Health
}