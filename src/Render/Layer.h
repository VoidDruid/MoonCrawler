#pragma once

#include <type_traits>
#include <functional>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>
#include "IDrawable.h"
#include "Utils/MappedIterator.hpp"
#include "ECS/Entity.h"

namespace MoonCrawler {
using DrawablesMap = std::unordered_map<GID, std::weak_ptr<IDrawable>>;
class Layer {
public:
    Layer() = default;
    void operator=(Layer const &x) = delete;

    template<typename T>
    GID addObject(const std::shared_ptr<T>& object) {
        static_assert(std::is_base_of<IDrawable, T>::value, "Object must be instance of IDrawable");

        GID id;
        if (object->ID == NO_ID) {
            return NO_ID;
        }
        id = object->ID;

        m_objectsMap[id] = std::move(std::weak_ptr<IDrawable>(object));
        return id;
    }

    void removeObject(GID id);

    std::optional<std::weak_ptr<IDrawable>>  getObject(GID id);

    MappedIterator<DrawablesMap, std::reference_wrapper<const sf::Sprite>> getSpritesIterator();

    MappedIterator<DrawablesMap, std::weak_ptr<IDrawable>> getDrawablesIterator();

private:
    DrawablesMap m_objectsMap{};
};
}
