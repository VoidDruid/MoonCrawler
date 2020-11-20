#pragma once

#include <QMainWindow>
#include "src/ui/GameCanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace MoonCrawler{
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    GameCanvas* getGameCanvas();
private:
    Ui::MainWindow *ui;
};
}