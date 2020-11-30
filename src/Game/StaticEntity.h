#pragma once

#include "Render/Components/StaticSprite.h"
#include "Scene.h"

namespace MoonCrawler {
struct StaticEntity : public StaticSprite, public EntityBase {
    bool isDrawable() override { return true; }

    void prepare(const std::shared_ptr<Scene> &scene) override;
    bool isKeyboardPlayable() override { return true; }
};
}
