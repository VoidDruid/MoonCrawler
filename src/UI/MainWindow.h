#pragma once

#include <memory>
#include <QMainWindow>

#include "UI/Canvas.h"
#include "Managers/GameManager.h"
#include "Managers/NetworkManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace MoonCrawler{
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    Canvas* getGameCanvas();

private:
    bool event(QEvent *event) override;

    Ui::MainWindow *ui;

    bool m_isHost;

    QStatusBar* m_statusBar = nullptr;

    QPushButton* m_playButton = nullptr;
    QPushButton* m_hostButton = nullptr;

    QPushButton* m_startButton = nullptr;

private slots:
    void handlePlayButton();
    void handleHostButton();
    void handleStartButton();
};
}