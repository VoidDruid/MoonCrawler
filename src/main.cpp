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

struct updateHealthRegeneration {
    void operator()(EntityID id, Components& components)
    {
        auto& health = components.healths[id];
        auto& position = components.positions[id];

        if(health.current < health.max) {
            ++health.current;
            std::cerr << "id: " << id << ", health: "<< health.current << std::endl;
        }
    }
    static const unsigned char neededComponents = (hasHealth | hasPosition);
};

int main(int argc, char **argv)
{
    initManagers();

    EntityID newID = 12;

    auto escManager = std::make_shared<ECSManager>();
    escManager->addComponent(newID, Position{0.0f, 0.0f});
    escManager->addComponent(newID, Health{100, 90});

    escManager->addComponent(13, Position{0.0f, 0.0f});
    escManager->addComponent(13, Health{100, 90});

    escManager->addComponent(1, Position{0.0f, 0.0f});
    escManager->addComponent(1, Health{10.0f, 0.0f});
    escManager->addComponent(1, Velocity{0.0f, 0.0f});

    escManager->addComponent(1222, Position{0.0f, 0.0f});

    std::thread ecsThread([escManager](){
        while(true) {
            for(auto& [id, options] : escManager->entities) {
                bool need = ((options & updateHealthRegeneration::neededComponents) == updateHealthRegeneration::neededComponents);
                if(need) {
                    updateHealthRegeneration{}(id, escManager->m_components);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
        }
    });
    ecsThread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(3));

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