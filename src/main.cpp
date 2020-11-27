#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"
#include "Managers/ECSManager.h"

#include <iostream>

using namespace MoonCrawler;

struct MyEntity : public Entity {
};

struct MySystem : public System {
    void operator()(EntityID id, Components& components) override{
        std::cerr << "ID: " << id << " " <<  components.positions[id].x << ":" << components.positions[id].y << std::endl;
    }
    inline const unsigned char getNeededComponents() override {
        return hasPosition;
    }
};

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

    auto ecsManager = std::make_shared<ECSManager>();
    ecsManager->addSystem<MySystem>();

    auto ent = std::make_shared<MyEntity>();
    ecsManager->addEntity(ent);
    ecsManager->addComponent(ent->ID, Position{10, 10});

    auto ent2 = std::make_shared<MyEntity>();
    ecsManager->addEntity(ent2);
    ecsManager->addComponent(ent2->ID, Position{103, 130});

    auto ent3 = std::make_shared<MyEntity>();
    ecsManager->addEntity(ent3);

    ecsManager->start();


    auto retVal = QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
}