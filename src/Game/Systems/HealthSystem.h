#pragma once

#include "ECS/System.h"

namespace MoonCrawler {
    class HealthSystem : public System {
    public:
        HealthSystem() = default;
        inline unsigned char getNeededComponents() override {
            return hasHealth;
        }
        void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) override;
    };
}
