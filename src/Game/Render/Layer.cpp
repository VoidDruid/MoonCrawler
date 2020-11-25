#include "Layer.h"

using namespace MoonCrawler;

const sf::Sprite& getSprites(const DrawablesMap::value_type& id_and_drawable) {
    return id_and_drawable.second->getSprite();
}

std::weak_ptr<IDrawable> getDrawables(const DrawablesMap::value_type& id_and_drawable) {
    return id_and_drawable.second;
}

MappedIterator<DrawablesMap, const sf::Sprite&> Layer::getSpritesIterator() {
    return MappedIterator<DrawablesMap, const sf::Sprite&>(m_objectsMap, getSprites);
}

MappedIterator<DrawablesMap, std::weak_ptr<IDrawable>> Layer::getDrawablesIterator() {
    return MappedIterator<DrawablesMap, std::weak_ptr<IDrawable>>(m_objectsMap, getDrawables);
}

void Layer::addObject(EntityID id,const std::shared_ptr<IDrawable>& object) {
    m_objectsMap[id] = std::move(object);
}

void Layer::removeObject(EntityID id) {
   m_objectsMap.erase(id);
}

std::shared_ptr<IDrawable> Layer::getObject(EntityID id) {
    auto object = m_objectsMap.find(id);
    if (object != m_objectsMap.end()) {
        return object->second;
    }
    return nullptr;
}
