#pragma once

#include "Render/Components/StaticSprite.h"
#include "Scene.h"

namespace MoonCrawler {
struct StaticEntity : public StaticSprite, public EntityBase {
    StaticEntity() {
        isDrawable = true;
        isKeyboardPlayable = false;
    }

    void prepare(const std::shared_ptr<Scene>& scene) override;
};
}
