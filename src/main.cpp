#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"

#include <iostream>

using namespace MoonCrawler;

#define DEBUGGING_RENDER
#ifdef DEBUGGING_RENDER
#include "Render/Canvas.h"
#include "Render/Resources/Texture.h"
#include "Game/Scene.h"
#include <Game/StaticEntity.h>
#include <Game/MainHeroIOSystem.h>

struct Mover : public System {
    void operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, Components& components) override {
        Position& position = components.get<Position>(entity->ID);
        position.x += 1;
    }
    unsigned char getNeededComponents() override {
        return hasPosition;
    }
};
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

#ifdef DEBUGGING_RENDER
    auto scene = createScene(mainWindow->getGameCanvas());
    auto staticEntityPtr = std::make_shared<StaticEntity>();
    auto texture = scene->getCanvas()->getResource<Texture>("test.png");

    staticEntityPtr->initialize(texture, sf::Vector2i(100, 100));
    staticEntityPtr->setPosition(sf::Vector2f(0, 0));

    auto id = scene->addObject<StaticEntity>(staticEntityPtr);
    scene->addComponent(id, Position{0, 0});
    scene->addSystem<MainHeroIOSystem>();
    scene->moveCamera(sf::Vector2f(0, 300));

    scene->start();

    qDebug() << id;
#endif

    auto retVal = QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
} catch(std::exception& exc) {
    std::cerr << exc.what() << std::endl;
    exit(-1);
}