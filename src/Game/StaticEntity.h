#pragma once

#include "Render/Components/StaticSprite.h"
#include "Scene.h"

namespace MoonCrawler {
struct StaticEntity : public StaticSprite, public EntityBase {
    bool isDrawable() override { return true; }
    bool isKeyboardPlayable() override { return isKeyboardPlayableV; }

    void prepare(const std::shared_ptr<Scene> &scene) override;

    bool isKeyboardPlayableV{false};
};
}
