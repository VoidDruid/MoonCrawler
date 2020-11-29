#include "Layer.h"

using namespace MoonCrawler;

inline std::optional<std::reference_wrapper<const sf::Sprite>> getSprite(const DrawablesMap::value_type& id_and_drawable) {
    if (auto strongDrawablePtr = id_and_drawable.second.lock()) {
        return strongDrawablePtr->getSprite();
    }
    return std::nullopt;
}

inline std::optional<std::weak_ptr<IDrawable>> getDrawable(const DrawablesMap::value_type& id_and_drawable) {
    if (auto strongDrawablePtr = id_and_drawable.second.lock()) {
        return strongDrawablePtr;
    }
    return std::nullopt;
}

MappedIterator<DrawablesMap, std::reference_wrapper<const sf::Sprite>> Layer::getSpritesIterator() {
    return MappedIterator<DrawablesMap, std::reference_wrapper<const sf::Sprite>>(m_objectsMap, getSprite);
}

MappedIterator<DrawablesMap, std::weak_ptr<IDrawable>> Layer::getDrawablesIterator() {
    return MappedIterator<DrawablesMap, std::weak_ptr<IDrawable>>(m_objectsMap, getDrawable);
}

void Layer::removeObject(GID id) {
   m_objectsMap.erase(id);
}

std::optional<std::weak_ptr<IDrawable>> Layer::getObject(GID id) {
    auto object = m_objectsMap.find(id);
    if (object != m_objectsMap.end()) {
        auto ptr = object->second;
        if (ptr.expired()) {
            m_objectsMap.erase(object->first);
            return std::nullopt;
        }
        return ptr;
    }
    return std::nullopt;
}
