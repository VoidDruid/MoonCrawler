#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"

#include <iostream>

using namespace MoonCrawler;


#define DEBUGGING_RENDER
#ifdef DEBUGGING_RENDER
#include "Render/Canvas.h"
#include "Render/Resources/Texture.h"
#include "Render/Components/StaticSprite.h"
#include "Game/Scene.h"

class StaticEntity : public StaticSprite, public EntityBase {
};
#endif

//#define DEBUGGING_ECS
#ifdef DEBUGGING_ECS
#include "Managers/ECSManager.h"
struct MyEntity : public EntityBase {
    void run() {
        auto myComponents = *m_components.lock();
        std::cout << myComponents.positions[ID].x << std::endl;
        std::cout << myComponents.healths[ID].value << std::endl;
    }
};

struct MySystem : public System {
    void operator()(GID id, Components& components) override{
        std::cerr << "MySystem ID: " << id << " " <<  components.positions[id].x << ":" << components.positions[id].y << std::endl;
    }
    inline unsigned char getNeededComponents() override {
        return hasPosition;
    }
};

struct PosSystem : public System {
    void operator()(GID id, Components& components) override{
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

void ecs() {
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

}
#endif

void initManagers(const std::shared_ptr<MainWindow>& mainWindow) {
    auto gameManager = initGameManager(mainWindow);
    auto networkManager = getNetworkManager();

    gameManager->addListener(networkManager);
    networkManager->addListener(gameManager);

    networkManager->init();
}

int main(int argc, char **argv) try
{
    QApplication app(argc, argv);

    auto mainWindow = std::make_shared<MainWindow>();
    initManagers(mainWindow);

    mainWindow->setWindowTitle("Moon Crawler");
    mainWindow->resize(800, 600);
    mainWindow->show();

#ifdef DEBUGGING_ECS
    ecs();
#endif

#ifdef DEBUGGING_RENDER
    auto scene = Scene(mainWindow->getGameCanvas());
    auto staticEntityPtr = std::make_shared<StaticEntity>();
    auto texture = scene.getCanvas()->getResource<Texture>("test.png");

    staticEntityPtr->initialize(texture, sf::Vector2i(100, 100));
    staticEntityPtr->setPosition(sf::Vector2f(0, 0));

    auto id = scene.addObject<StaticEntity>(staticEntityPtr);
    scene.moveCamera(sf::Vector2f(0, 300));

    qDebug() << id;
#endif

    auto retVal = QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
} catch(std::exception& exc) {
    std::cerr << exc.what() << std::endl;
}