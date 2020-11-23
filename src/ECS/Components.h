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