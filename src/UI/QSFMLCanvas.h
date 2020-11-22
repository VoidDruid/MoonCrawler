#pragma once

#include <SFML/Graphics.hpp>
#include <QtWidgets>

namespace MoonCrawler {
class QSFMLCanvas : public QWidget, public sf::RenderWindow {
public:
    explicit QSFMLCanvas(QWidget *parent);

    virtual ~QSFMLCanvas() = default;

    virtual void setFrameTime(int frameTime);

private:
    virtual void onInit() {};

    virtual void onUpdate() {};

    QPaintEngine *paintEngine() const override;

    void showEvent(QShowEvent *) override;

    void paintEvent(QPaintEvent *) override;

    QTimer m_timer;
    bool m_isInitialized;
};
}