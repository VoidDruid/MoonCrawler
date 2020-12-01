#pragma once

#include <cstdint>
#include <tuple>
#include <optional>
#include <nlohmann/json.hpp>

#include "Components.h"
#include "meta.h"

namespace MoonCrawler {
constexpr GID NO_ID = 0;

struct EntityBase {
    unsigned char hasComponents{0x00};
    GID ID{NO_ID};
    std::shared_ptr<Components> m_components{};

    virtual bool isKeyboardPlayable() { return true; }
    virtual bool isDrawable() { return false; }  // Hack for integration with render system

    template<typename T>
    bool has() const {
        auto flag = getBitFlag<T>();
        return (hasComponents & flag) == flag;
    }
};

#define ADD_COMPONENT_TO_JSON(ComponentT, component) \
if(e.has<ComponentT>()) {                            \
    j["components"][#ComponentT] = e.m_components->component[e.ID];\
}


#define GET_COMPONENT_FROM_JSON(ComponentT, component) \
if(e.has<ComponentT>()) {                              \
    e.m_components->component[e.ID] = j["components"][#ComponentT]; \
}

inline void to_json(nlohmann::json& j, const EntityBase& e) {
    auto components = nlohmann::json();
    j = nlohmann::json{
        {"ID", e.ID},
        {"hasComponents", e.hasComponents},
    };
    ADD_COMPONENT_TO_JSON(Position, positions);
    ADD_COMPONENT_TO_JSON(Health, healths);
}

inline void from_json(const nlohmann::json& j, EntityBase& e) {
    j.at("ID").get_to(e.ID);
    j.at("hasComponents").get_to(e.hasComponents);

    if(not e.m_components) {
        e.m_components = std::make_shared<Components>();
    }

    GET_COMPONENT_FROM_JSON(Position, positions);
    GET_COMPONENT_FROM_JSON(Health, healths);
}


GID generateId();
}