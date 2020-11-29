#pragma once

#include <cstdint>
#include <tuple>
#include <optional>

#include "Components.h"
#include "meta.h"

namespace MoonCrawler {
constexpr GID NO_ID = 0;

struct EntityBase {
    unsigned char hasComponents{0x00};
    GID ID{NO_ID};
    std::weak_ptr<Components> m_components{};
};

GID generateId();
}