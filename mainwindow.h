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
    explicit MainWindow(QWidget *parent = 0,
                        QLabel* unexposed_label = nullptr,
                        std::vector<QPushButton*> b = std::vector<QPushButton*>());
    ~MainWindow();
    void execute();
private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> buttons;
    const int num_of_rows = 7;
    const int num_of_cols = 7;
    const int num_of_bombs = 3;

public slots:
void clickedSlot();
};
#endif // MAINWINDOW_H
