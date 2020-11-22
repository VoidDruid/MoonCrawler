#include "ui/MainWindow.h"
#include "Managers/GameManager.h"
#include "Managers/NetworkManager.h"

#include <tuple>
#include <iostream>

using namespace MoonCrawler;
std::tuple<std::shared_ptr<GameManager>, std::shared_ptr<NetworkManager>>
initManagers() {
    auto gameManager = std::make_shared<GameManager>();
    auto networkManager = std::make_shared<NetworkManager>();

    gameManager->addListener(networkManager);
    networkManager->addListener(gameManager);

    networkManager->init();

    return {gameManager, networkManager};
}

bool isHost(int argc, char **argv) {
    if(argc < 2) {
        std::cerr << "Provide configuration" << std::endl;
        std::exit(1);
    }
    if(std::strcmp(argv[1], "client") == 0) {
        return false;
    }
    else {
        return true;
    }

}
int main(int argc, char **argv)
{
    auto managers = initManagers();
    auto& gameManager = std::get<std::shared_ptr<GameManager>>(managers);

    auto startGame = [&gameManager, argv, argc]() {
        gameManager->startGame(isHost(argc, argv));
    };

    std::thread gameThread(startGame);
    gameThread.detach();

    QApplication app(argc, argv);

    auto mainWindow = new MoonCrawler::MainWindow();

    mainWindow->setWindowTitle("Qt SFML");
    mainWindow->resize(800, 600);
    mainWindow->show();

    auto canvas = mainWindow->getGameCanvas();

    return QApplication::exec();
}
