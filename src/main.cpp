#include <QtCore>
#include <QtWidgets>

#include <iostream>

#include "src/Managers/NetworkManager.h"
#include "src/Managers/GameManager.h"
#include "NetworkPAL/NetworkLinuxPAL.h"

using namespace MoonCrawler;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        throw std::runtime_error("Provide argv");
    }

    QApplication app(argc, argv);
    auto dialog = std::make_unique<QDialog>();
    auto label = std::make_unique<QLabel>(dialog.get());
    label->setText("<font color=red>Hello, World!</font>");
    dialog->show();

    auto gameManager = std::make_shared<GameManager>();
    auto networkManager = std::make_shared<NetworkManager>();

    networkManager->addListener(gameManager);
    gameManager->addListener(networkManager);

    auto weakGameManager = std::weak_ptr<GameManager>(gameManager);
    auto weakNetworkManager = std::weak_ptr<NetworkManager>(networkManager);

    if(std::strcmp(argv[1],"client") == 0) {
        gameManager->startGame(false);
    }
    else if(std::strcmp(argv[1],"server") == 0) {
        gameManager->startGame(true);
    }
    else {
        throw std::runtime_error("Invalid argv");
    }

    auto networkLayer = [argv, weakGameManager, weakNetworkManager]() {
        auto gameManager = weakGameManager.lock();
        auto networkManager = weakNetworkManager.lock();

        if(gameManager and networkManager) {
            networkManager->init();
        }
    };

    std::thread network(networkLayer);
    network.detach();

    return QApplication::exec();
}
