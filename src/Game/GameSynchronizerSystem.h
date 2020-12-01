#pragma once
#include "ECS/System.h"
#include "Listener.h"

namespace MoonCrawler {
class GameSynchronizerSystem : public System, public Listener, public std::enable_shared_from_this<GameSynchronizerSystem> {
public:
    GameSynchronizerSystem() = default;
    void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) override;
    inline unsigned char getNeededComponents() override {
        return hasTransform;
    }
    void onEvent(Event& event) override;
private:
    bool m_registered{false};
    std::weak_ptr<Scene> m_scene{};
};
}