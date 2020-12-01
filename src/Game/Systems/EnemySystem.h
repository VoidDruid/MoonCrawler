#pragma once

#include "ECS/System.h"

namespace MoonCrawler {
class EnemySystem : public System {
public:
    EnemySystem() = default;
    inline unsigned char getNeededComponents() override {
        return hasEnemyTrait | hasTransform;
    }
    void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) override;
};
}