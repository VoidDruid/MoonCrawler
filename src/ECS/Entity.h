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

    bool isKeyboardPlayable{false};
    bool isDrawable{false};
    bool isDynamic{false};

    template<typename T>
    bool has() const {
        auto flag = getBitFlag<T>();
        return (hasComponents & flag) == flag;
    }
};

#define ADD_COMPONENT_TO_JSON(ComponentT) \
if(e.has<ComponentT>()) {                            \
    j["components"][#ComponentT] = e.m_components->get<ComponentT>(e.ID);\
}


#define GET_COMPONENT_FROM_JSON(ComponentT) \
if(e.has<ComponentT>()) {                              \
    e.m_components->add<ComponentT>(e.ID, j["components"][#ComponentT]); \
}

inline void to_json(nlohmann::json& j, const EntityBase& e) {
    auto components = nlohmann::json();
    j = nlohmann::json{
        {"ID", e.ID},
        {"hasComponents", e.hasComponents},
        {"isKeyboardPlayable", e.isKeyboardPlayable},
        {"isDrawable", e.isDrawable},
        {"isDynamic", e.isDynamic}
    };
    ADD_COMPONENT_TO_JSON(Transform);
    ADD_COMPONENT_TO_JSON(Health);
    ADD_COMPONENT_TO_JSON(Collider);
    ADD_COMPONENT_TO_JSON(EnemyTrait);
}

inline void from_json(const nlohmann::json& j, EntityBase& e) {
    j.at("ID").get_to(e.ID);
    j.at("hasComponents").get_to(e.hasComponents);
    j.at("isKeyboardPlayable").get_to(e.isKeyboardPlayable);
    j.at("isDrawable").get_to(e.isDrawable);
    j.at("isDynamic").get_to(e.isDynamic);

    if(not e.m_components) {
        e.m_components = std::make_shared<Components>();
    }

    GET_COMPONENT_FROM_JSON(Transform);
    GET_COMPONENT_FROM_JSON(Health);
    GET_COMPONENT_FROM_JSON(Collider);
    GET_COMPONENT_FROM_JSON(EnemyTrait);
}


GID generateId();
}