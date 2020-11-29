#pragma once

#include <SFML/Graphics.hpp>
#include <QtWidgets>

namespace MoonCrawler {
class QSFMLCanvas : public QWidget, public sf::RenderWindow {
public:
    explicit QSFMLCanvas(QWidget *parent);

    QSFMLCanvas(QSFMLCanvas const &) = delete;

    void operator=(QSFMLCanvas const &x) = delete;

    QSFMLCanvas(QSFMLCanvas&&) = delete;

    virtual ~QSFMLCanvas() = default;

    virtual void setFrameTime(int frameTime);

private:
    virtual void onInit() {};

    virtual void onUpdate() {};

    virtual void onAfterUpdate() {};

    virtual void onEvent(const sf::Event& event) {};

    QPaintEngine *paintEngine() const override;

    void showEvent(QShowEvent *) override;

    void paintEvent(QPaintEvent *) override;

    QTimer m_timer;

    bool m_isInitialized;


};
}