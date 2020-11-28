#pragma once

#include "Managers/ECSManager.h"
#include "Render/Canvas.h"
#include "Render/IDrawable.h"


namespace MoonCrawler {
class Scene {
public:
    explicit Scene(Canvas* canvas);

    Scene(Scene const &) = delete;
    void operator=(Scene const &x) = delete;
    Scene(Scene&&) = delete;

    void addDrawable(const std::shared_ptr<IDrawable>& drawable);
private:
    ECSManager m_ecsManager{};
    Canvas* m_canvas;
};
}
