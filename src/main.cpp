#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"
#include "Managers/ECSManager.h"

#include <iostream>

using namespace MoonCrawler;

struct MyEntity : public EntityBase {
    void run() {
        auto myComponents = *m_components.lock();
        std::cout << myComponents.positions[ID].x << std::endl;
        std::cout << myComponents.healths[ID].value << std::endl;
    }
};

struct MySystem : public System {
    void operator()(EntityID id, Components& components) override{
        std::cerr << "MySystem ID: " << id << " " <<  components.positions[id].x << ":" << components.positions[id].y << std::endl;
    }
    inline unsigned char getNeededComponents() override {
        return hasPosition;
    }
};

struct PosSystem : public System {
    void operator()(EntityID id, Components& components) override{
        std::cerr << "PosSystem ID: " << id << " " <<  components.positions[id].x << ":" << components.positions[id].y << std::endl;
        std::cerr << "PosSystem ID: " << id << " " <<  components.healths[id].value << std::endl;
        if(components.healths[id].value > 100) {
            components.healths[id].value--;
        }
    }
    inline unsigned char getNeededComponents() override {
        return hasPosition | hasHealth;
    }
};

void initManagers() {
    auto gameManager = getGameManager();
    auto networkManager = getNetworkManager();

    gameManager->addListener(networkManager);
    networkManager->addListener(gameManager);

    networkManager->init();
}

int main(int argc, char **argv) try
{
    QApplication app(argc, argv);

    auto mainWindow = std::make_shared<MainWindow>();
    initManagers();

    mainWindow->setWindowTitle("Moon Crawler");
    mainWindow->resize(800, 600);
    mainWindow->show();

    auto ecsManager = std::make_shared<ECSManager>();
    ecsManager->addSystem<MySystem>();
    ecsManager->addSystem<PosSystem>();

    auto ent = std::make_shared<MyEntity>();
    ecsManager->addEntity(ent);
    ecsManager->addComponent(ent->ID, Position{10, 10});

    auto ent2 = std::make_shared<MyEntity>();
    ecsManager->addEntity(ent2);
    ecsManager->addComponent(ent2->ID, Position{103, 130});
    ecsManager->addComponent(ent2->ID, Health{100500});

    auto ent3 = std::make_shared<MyEntity>();
    ecsManager->addEntity(ent3);
    ent3->run();

    ecsManager->start();

    auto retVal = QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
} catch(std::exception& exc) {
    std::cerr << exc.what() << std::endl;
}