#include "ResourceManager.h"
#include "Texture.hpp"

#include <utility>
#include <fstream>

using namespace MoonCrawler;

const std::string TEXTURES_ROOT = "textures";
const std::string LAYOUTS_ROOT = "layouts";

ResourceManager::ResourceManager(const std::filesystem::path& sourceDir) :
    m_texturesDir(sourceDir / TEXTURES_ROOT), m_layoutsDir(sourceDir / LAYOUTS_ROOT)
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

template <>
std::shared_ptr<Layout> ResourceManager::get(const std::string& resourceName) {
    auto key = "layout_" + resourceName;
    auto ind = m_resourceMap.find(key);
    if (ind != m_resourceMap.end()) {
        return std::get<std::shared_ptr<Layout>>(ind->second);
    }

    std::ifstream resourceFile(m_layoutsDir / resourceName);
    nlohmann::json layoutData;
    resourceFile >> layoutData;
    auto layout = std::make_shared<Layout>(layoutData);

    m_resourceMap[key] = ResourceType(layout);
    return layout;
}