#include "GameManager.h"
#include "Event.h"

#include <iostream>

using namespace MoonCrawler;

void GameManager::OnEvent(Event& event) {
    std::cout << "OnEvent: " << event << std::endl;
    event.MarkStale();
}
