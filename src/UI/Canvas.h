#pragma once

#include "QSFMLCanvas.h"

namespace MoonCrawler {
class Canvas : public QSFMLCanvas {
public :
    explicit Canvas(QWidget* Parent);
private :
    void onInit() override;
    void onUpdate() override;
};
}