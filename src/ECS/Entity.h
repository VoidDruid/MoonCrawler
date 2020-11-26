#pragma once

#include <cstdint>
namespace MoonCrawler {

using EntityID = uint64_t;
struct Entity {
    int components = 0x00;
    EntityID ID{};
};

EntityID generateId();
}