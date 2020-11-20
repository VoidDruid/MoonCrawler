#include "ui/MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto mainWindow = new MoonCrawler::MainWindow();

    mainWindow->setWindowTitle("Qt SFML");
    mainWindow->resize(800, 600);
    mainWindow->show();

    auto canvas = mainWindow->getGameCanvas();

    return app.exec();
}
