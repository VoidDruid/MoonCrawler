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

    auto gameManager = std::make_shared<GameManager>();
    auto networkManager = std::make_shared<NetworkManager>();
    networkManager->addListener(gameManager);
    networkManager->init();
    networkManager->run();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    auto data = R"({"game_state" : "start"})"_json;
    Event event{
            data,
            EventType::GameEvent,
            EventStatus::New};
    while(true) {
        int a = 10;
        std::cout << "here" << std::endl;
        std::cin >> a;
        std::cout << "here2" << std::endl;
        if(a == 200) {
            std::cout << "here3" << std::endl;
            std::string data2;
            std::cin >> data2;
            networkManager->sendData(event);
            std::cout << "here4" << std::endl;
        }
        if(a == 1) {
            break;
        }
    }

    //NetworkLinuxPAL pal;
    //pal.initServer("ss", 9999);

    /*if(pal.isConnected()) {
        pal.sendData();
    }*/

    //return QApplication::exec();
}
