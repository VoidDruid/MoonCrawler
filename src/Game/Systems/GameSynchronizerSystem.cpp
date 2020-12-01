#include "GameMasterIOSystem.h"

#include "Game/Scene.h"
#include "GameSynchronizerSystem.h"
#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"
#include "Subsystems/Entities.h"

#include <iostream>

void MoonCrawler::GameSynchronizerSystem::operator()(
        std::shared_ptr<Scene> scene,
        std::shared_ptr<EntityBase> entity,
        MoonCrawler::Components &components) {
    if(not m_registered) {
        auto networkManager = getNetworkManager();
        networkManager->addListener(shared_from_this());
        m_scene = scene;
        m_registered = true;
    }

    if(getGameManager()->isHost()) {
        return;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(60));

    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    //{
    auto& position = components.get<Transform>(entity->ID);
        nlohmann::json js;
        to_json(js, *entity);

        auto networkManager = getNetworkManager();
        js["gameState"] = "inGame";
        Event event{
                js,
                EventType::GameEvent,
                EventStatus::New
        };
        networkManager->sendEvent(event);
   // }
}

void MoonCrawler::GameSynchronizerSystem::onEvent(MoonCrawler::Event &event) {
    auto data= *event.getData();
    if((data["gameState"] == "inGame") && (data["isRemote"] == true) && (event.getEventStatus() == EventStatus::New)) {
        if(data["isDynamic"] == true) {
            auto ent = std::make_shared<StaticEntity>();
            from_json(data, *ent);
            to_json(data, *ent);
           // std::cout << "Received from NETWORK : " << data << std::endl;
            if(auto strongScene = m_scene.lock()) {
                strongScene->updateEntity(ent);
            }
        }
    }
}
