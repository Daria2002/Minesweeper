#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "minesweeper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Game* game;
    QLabel* ul;
    explicit MainWindow(QWidget *parent = 0, QLabel* unexposed_label = nullptr, std::vector<QPushButton*> buttons = std::vector<QPushButton*>());
    ~MainWindow();
    void execute();
private:
    Ui::MainWindow *ui;

public slots:
void clickedSlot();
};
#endif // MAINWINDOW_H
