#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"

#include <iostream>

using namespace MoonCrawler;

#define DEBUGGING_RENDER
#ifdef DEBUGGING_RENDER
#include "Render/Canvas.h"
#include "Game/Scene.h"

#include "Game/Systems/MainHeroIOSystem.h"
#include "Game/Systems/EnemySystem.h"
#include "Game/Systems/GameSynchronizerSystem.h"
#include "Game/Systems/HealthSystem.h"
#include "Game/Systems/Subsystems/Entities.h"
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
    createPlayer(scene, Transform{0, 0, 7, 7});
    createEnemy(scene, {40, 40, 5, 5});
    scene->populate("map.json");

    scene->addSystem<MainHeroIOSystem>();
    scene->addSystem<GameSynchronizerSystem>();
    scene->addSystem<EnemySystem>();
    scene->addSystem<HealthSystem>();

    scene->moveCamera(sf::Vector2f(0, 0));

    scene->start();
#endif
    auto retVal = QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
} catch(std::exception& exc) {
    std::cerr << exc.what() << std::endl;
    exit(-1);
}