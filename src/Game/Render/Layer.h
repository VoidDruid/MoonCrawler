#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>
#include "IDrawable.h"
#include "Utils/MappedIterator.hpp"

namespace MoonCrawler {
using EntityID = uint64_t;
using DrawablesMap = std::unordered_map<EntityID, std::shared_ptr<IDrawable>>;

class Layer {
public:
    void addObject(EntityID id, const std::shared_ptr<IDrawable>& object);

    void removeObject(EntityID id);

    std::shared_ptr<IDrawable> getObject(EntityID id);

    MappedIterator<DrawablesMap, const sf::Sprite&> getSpritesIterator();

    MappedIterator<DrawablesMap, std::weak_ptr<IDrawable>> getDrawablesIterator();

private:
    DrawablesMap m_objectsMap{};
};
}
