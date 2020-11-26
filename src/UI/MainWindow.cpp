#include "UI/MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>

using namespace MoonCrawler;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), m_isHost(false)
{
    ui->setupUi(this);
    m_hostButton = ui->hostButton;
    m_playButton = ui->playButton;
    m_startButton = ui->startButton;
    m_statusBar = ui->statusBar;

    connect(m_hostButton, SIGNAL (released()), this, SLOT (handleHostButton()));
    connect(m_playButton, SIGNAL(released()), this, SLOT(handlePlayButton()));
    connect(m_startButton, SIGNAL(released()), this, SLOT(handleStartButton()));
}

void MainWindow::handlePlayButton() {
    m_isHost = false;
    m_statusBar->showMessage("Pressed <play> button");
}

void MainWindow::handleHostButton() {
    m_isHost = true;
    m_statusBar->showMessage("Pressed <host> button");
}

void MainWindow::handleStartButton() {
    getGameManager()->startGame(m_isHost);
    m_statusBar->showMessage("Pressed <start> button");
}

MainWindow::~MainWindow()
{
    delete ui;
}

Canvas* MainWindow::getGameCanvas() {
    return ui->gameCanvas;
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        auto *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Tab) {
            // special tab handling here
            std::cout << "hehe tab" << std::endl;
            return true;
        }
    }

    return QWidget::event(event);
}

#include "moc_MainWindow.cpp"
