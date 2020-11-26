#include "ECSManager.h"

using namespace MoonCrawler;

void ECSManager::ecsLoop() {
    while(true) {
        for(auto& [id, options] : m_EntityComponentFlags) {
            for (auto& system : m_Systems) {
                unsigned char neededComponentsFlag = system->getNeededComponents();
                bool hasComponents = (options & neededComponentsFlag) == neededComponentsFlag;
                if(hasComponents) {
                    system->operator()(id, m_components);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (m_milSecsLoopPause));
    }
}

void ECSManager::start() {
    ecsThread = std::thread(&ECSManager::ecsLoop, this);
    ecsThread.detach();
}
