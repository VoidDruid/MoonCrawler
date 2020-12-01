#pragma once

#include "ECS/System.h"

namespace MoonCrawler {
class GameMasterIOSystem : public System {
public:
    GameMasterIOSystem() = default;
    void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) override;
    inline unsigned char getNeededComponents() override {
        return hasPosition;
    }
};
}