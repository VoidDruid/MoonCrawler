#include "ResourceManager.h"
#include "Texture.h"

#include <utility>

using namespace MoonCrawler;

const std::string TEXTURES_ROOT = "textures";

ResourceManager::ResourceManager(const std::filesystem::path& sourceDir) :
    m_texturesDir(sourceDir / TEXTURES_ROOT)
{}

template <>
std::shared_ptr<Texture> ResourceManager::get(const std::string& resourceName) {
    auto key = "texture_" + resourceName;
    auto ind = m_resourceMap.find(key);
    if (ind != m_resourceMap.end()) {
        return std::get<std::shared_ptr<Texture>>(ind->second);
    }

    auto texture = std::make_shared<Texture>();
    texture->loadFromFile(m_texturesDir / resourceName);

    m_resourceMap[key] = ResourceType(texture);
    return texture;
}
