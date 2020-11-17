#include <QtCore>
#include <QtWidgets>

#include <iostream>

#include "NetworkManager.h"
#include "GameManager.h"
#include "NetworkPAL/NetworkLinuxPAL.h"

using namespace MoonCrawler;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto dialog = std::make_unique<QDialog>();
    auto label = std::make_unique<QLabel>(dialog.get());
    label->setText("<font color=red>Hello, World!</font>");
    dialog->show();

    auto networkLayer = [argv]() {
        auto gameManager = std::make_shared<GameManager>();
        auto networkManager = std::make_shared<NetworkManager>();
        networkManager->addListener(gameManager);
        networkManager->init();
        if(std::strcmp(argv[1],"client") == 0) {
            networkManager->startClient();
        }

        if(std::strcmp(argv[1],"server") == 0) {
            networkManager->startServer();
        }

        auto data = R"({"game_state" : "start"})"_json;
        Event event{
                data,
                EventType::GameEvent,
                EventStatus::New};
        while(true) {
            int a{};
            std::cin >> a;
            if (a == 200) {
                networkManager->sendData(event);
            }
            if (a == 1) {
                break;
            }
        }
    };

    std::thread network(networkLayer);
    network.detach();

    return QApplication::exec();
}
