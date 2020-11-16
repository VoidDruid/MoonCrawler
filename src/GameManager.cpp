#include "GameManager.h"
#include "Event.h"

#include <iostream>

using namespace MoonCrawler;

void GameManager::onEvent(Event& event) {
    std::cout << "onEvent: " << event << std::endl;
    event.markStale();
}
