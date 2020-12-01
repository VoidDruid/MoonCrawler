#pragma once

#include "Listener.h"
#include "Subscriber.h"
#include "UI/MainWindow.h"

#include <list>
#include <variant>

namespace MoonCrawler {
class Event;

class GameManager : public Listener, public Subscriber {
public:
    explicit GameManager(const std::shared_ptr<MainWindow>& mainWindow);

    GameManager(const GameManager&) = delete;

    GameManager& operator=(const GameManager&) = delete;

    void onEvent(Event& event) override;

    void addListener(const std::shared_ptr<Listener>& listener) override;

    void startGame(bool isHost);

    bool isHost() { return m_isHost; }

private:
    void sendEvent(Event& event);

    struct Initialized {};
    struct Starting {};
    struct Started {};
    struct InGame {};
    struct EndOfGame {};

    std::variant<Initialized, Starting, Started, InGame, EndOfGame> m_state{Initialized{}};

    std::list<std::weak_ptr<Listener>> m_listeners{};

    bool m_isHost{false};

    std::shared_ptr<MainWindow> m_mainWindow;
};

std::shared_ptr<GameManager> getGameManager();
std::shared_ptr<GameManager> initGameManager(const std::shared_ptr<MainWindow>& mainWindow);
}