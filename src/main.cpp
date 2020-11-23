#include "UI/MainWindow.h"

#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"

#include "ECS/Components.h"
#include "Managers/ECSManager.h"

#include <iostream>

using namespace MoonCrawler;

void initManagers() {
    auto gameManager = getGameManager();
    auto networkManager = getNetworkManager();

    gameManager->addListener(networkManager);
    networkManager->addListener(gameManager);

    networkManager->init();
}

void updateHealthRegeneration(int64_t currentFrame, Healths& healths)
{
    if(currentFrame == 10)
    {
        for(auto& [id, health] : healths)
        {
            if(health.current < health.max) {
                ++health.current;
                std::cerr << id << ":"<< health.current << std::endl;
            }
        }
    }
}

int main(int argc, char **argv)
{
    initManagers();

    EntityID newID = 12;

    auto escManager = std::make_shared<ECSManager>();
    escManager->addComponent(newID, Position{0.0f, 0.0f});
    escManager->addComponent(newID, Health{100, 90});

    std::thread ecsThread([escManager](){
        while(true) {
            updateHealthRegeneration(10, escManager->m_components.healths);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    ecsThread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    escManager->removeComponent(newID, Health{});

    QApplication app(argc, argv);

    auto mainWindow = new MoonCrawler::MainWindow();

    mainWindow->setWindowTitle("Qt SFML");
    mainWindow->resize(800, 600);
    mainWindow->show();

    auto canvas = mainWindow->getGameCanvas();

    auto retVal =  QApplication::exec();
    getNetworkManager()->shutdown();

    return retVal;
}