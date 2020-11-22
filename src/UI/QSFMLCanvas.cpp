#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif
#include "UI/QSFMLCanvas.h"

using namespace MoonCrawler;

const int mSecPerFrame60 = 1000 / 60;

QSFMLCanvas::QSFMLCanvas(QWidget* parent) :
    QWidget         (parent),
    m_isInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);

    m_timer.setInterval(mSecPerFrame60);
}

void QSFMLCanvas::setFrameTime(int frameTime) {
    m_timer.setInterval(frameTime);
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!m_isInitialized)
    {
#ifdef Q_WS_X11
        XFlush(QX11Info::display());
#endif
        RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));
        onInit();

        // Setup the timer to trigger a refresh at specified frame rate
        connect(&m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
        m_timer.start();

        m_isInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return nullptr;  // tell Qt we are not using it paint engine
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    onUpdate();
    display();
}
