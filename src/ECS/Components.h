#pragma once

#include <unordered_map>

namespace MoonCrawler {

struct Velocity {
    float x;
    float y;
};

struct Health {
    float max;
    float current;
};

struct Position {
    float x;
    float y;
};

constexpr unsigned char hasVelocity = 0x01; // шестнадцатеричный литерал для 0000 0001
constexpr unsigned char hasHealth = 0x02; // шестнадцатеричный литерал для 0000 0010
constexpr unsigned char hasPosition = 0x04; // шестнадцатеричный литерал для 0000 0100
/*constexpr unsigned char __ = 0x08; // шестнадцатеричный литерал для 0000 1000
constexpr unsigned char __ = 0x10; // шестнадцатеричный литерал для 0001 0000
constexpr unsigned char __ = 0x20; // шестнадцатеричный литерал для 0010 0000
constexpr unsigned char __ = 0x40; // шестнадцатеричный литерал для 0100 0000
constexpr unsigned char __ = 0x80; // шестнадцатеричный литерал для 1000 0000
*/
using EntityID = uint64_t;

template <typename Type>
using ComponentMap = std::unordered_map<EntityID, Type>;

using Positions = ComponentMap<Position>;
using Velocities = ComponentMap<Velocity>;
using Healths = ComponentMap<Health>;

struct Components
{
    Positions positions;
    Velocities velocities;
    Healths healths;
};
}