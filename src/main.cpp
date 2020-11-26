#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"
#include "Managers/ECSManager.h"

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
    QApplication app(argc, argv);

    auto mainWindow = std::make_shared<MainWindow>();
    initManagers();

    mainWindow->setWindowTitle("Moon Crawler");
    mainWindow->resize(800, 600);
    mainWindow->show();

    auto retVal = QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
}