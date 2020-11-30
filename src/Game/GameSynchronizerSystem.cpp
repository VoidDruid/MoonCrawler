#include "GameMasterIOSystem.h"

#include "Scene.h"
#include "GameSynchronizerSystem.h"
#include "Managers/NetworkManager.h"
#include "Managers/GameManager.h"
#include <iostream>

void MoonCrawler::GameSynchronizerSystem::operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity,
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
        //std::cout << "Current Entity with ID = " << entity->ID << std::endl;
        static Position prevPos{};
        auto& position = components.positions[entity->ID];

        if(prevPos.x == position.x && prevPos.y == position.y) {
            return;
        }
        prevPos = position;
    /*nlohmann::json js;
    to_json(js, position);
    std::cout << js << std::endl;

    Position pos{};
    from_json(js, pos);
    std::cout << pos.x << " " << pos.y << std::endl;*/

        nlohmann::json js;
        to_json(js, *entity);
        //std::cout << "Entity: " << js << std::endl;

        /*EntityBase ent{};
        from_json(js, ent);
        to_json(js, ent);
        std::cout << "from_json: " <<js << std::endl;*/
        auto networkManager = getNetworkManager();
        js["gameState"] = "inGame";
        Event event{
                js,
                EventType::GameEvent,
                EventStatus::New
        };
        networkManager->sendEvent(event);
    //}
}

void MoonCrawler::GameSynchronizerSystem::onEvent(MoonCrawler::Event &event) {
    auto data= *event.getData();
    if((data["gameState"] == "inGame") && (data["isRemote"] == true) && (event.getEventStatus() == EventStatus::New)) {
        EntityBase ent{};
        from_json(data, ent);
        to_json(data, ent);
        std::cout << "Received from NETWORK : " << data << std::endl;

        if(auto strongScene = m_scene.lock()) {
            strongScene->updateEntity(std::make_shared<EntityBase>(ent));
        }
    }
}
