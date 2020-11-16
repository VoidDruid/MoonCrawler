#include <QtCore>
#include <QtWidgets>

#include <iostream>

#include "NetworkManager.h"
#include "GameManager.h"

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
    networkManager->run();

    return QApplication::exec();
}
