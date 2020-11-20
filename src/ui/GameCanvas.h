#pragma once

#include "QSFMLCanvas.h"

namespace MoonCrawler {
class GameCanvas : public QSFMLCanvas {
public :
    explicit GameCanvas(QWidget* Parent);
private :
    void onInit() override;
    void onUpdate() override;
};
}