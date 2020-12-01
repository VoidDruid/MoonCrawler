#pragma once

#include "ECS/System.h"

namespace MoonCrawler {
class MainHeroIOSystem : public System {
public:
    MainHeroIOSystem() = default;
    void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) override;
    inline unsigned char getNeededComponents() override {
        return hasTransform;
    }
};
}