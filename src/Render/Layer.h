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
template <class T> using is_drawable_entity = typename std::enable_if<
    std::is_base_of_v<IDrawable, T> &&
    std::is_base_of_v<EntityBase, T>>;

class Layer {
public:
    Layer() = default;
    void operator=(Layer const &x) = delete;

    template <typename T>
    GID  addObject(const std::shared_ptr<T>& object);

    template <typename T, is_drawable_entity<T>>
    GID addObject(const std::shared_ptr<T>& object) {
        if (object->ID == NO_ID) {
            return NO_ID;
        }
        m_objectsMap[object->ID] = object;
        return object->ID;
    }

    template <> GID addObject<IDrawable>(const std::shared_ptr<IDrawable>& object) {
        GID id = generateId();
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
