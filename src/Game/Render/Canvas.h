#pragma once

#include "UI/QSFMLCanvas.h"
#include "Resources/ResourceManager.h"
#include "IDrawable.h"
#include "Layer.h"

namespace MoonCrawler {
class Canvas : public QSFMLCanvas {
public :
    explicit Canvas(QWidget* Parent);

    void draw(const IDrawable& drawable);

    void draw(const std::shared_ptr<IDrawable>& drawable);

    template <class T> std::shared_ptr<T> get(std::string resourceName);

private :
    void onInit() override;

    void onUpdate() override;

    ResourceManager m_resourceManager;
    std::vector<Layer> m_Layers{};
};
}