#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"

using namespace MoonCrawler;

void initManagers() {
    auto gameManager = getGameManager();
    auto networkManager = getNetworkManager();

    gameManager->addListener(networkManager);
    networkManager->addListener(gameManager);

    networkManager->init();
}

int main(int argc, char **argv)
{
    initManagers();
    QApplication app(argc, argv);

    auto mainWindow = new MoonCrawler::MainWindow();

    mainWindow->setWindowTitle("Qt SFML");
    mainWindow->resize(800, 600);
    mainWindow->show();

    auto canvas = mainWindow->getGameCanvas();

    auto retVal =  QApplication::exec();
    getNetworkManager()->shutdown();
    return retVal;
}
