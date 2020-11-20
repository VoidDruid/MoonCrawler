#include "ui/MainWindow.h"
#include "ui_MainWindow.h"

using namespace MoonCrawler;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

GameCanvas* MainWindow::getGameCanvas() {
    return ui->gameCanvas;
}

#include "moc_MainWindow.cpp"
