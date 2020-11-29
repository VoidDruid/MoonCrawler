#pragma once

#include <unordered_map>
#include <variant>
#include <filesystem>

#include "Texture.h"

namespace MoonCrawler {
class ResourceManager {
public:
    explicit ResourceManager(const std::filesystem::path& sourceDir);
    template <class T> std::shared_ptr<T> get(const std::string& resourceName);
private:
    using ResourceType = std::variant<std::shared_ptr<Texture>>;
    std::unordered_map<std::string, ResourceType> m_resourceMap{};

    std::filesystem::path m_texturesDir;
};
}
