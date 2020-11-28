#pragma once

#include <cstdint>
#include <tuple>
#include <optional>

#include "Components.h"
#include "meta.h"

namespace MoonCrawler {

struct EntityBase {
    unsigned char hasComponents{0x00};
    EntityID ID{};
    std::weak_ptr<Components> m_components{};
};

EntityID generateId();
}