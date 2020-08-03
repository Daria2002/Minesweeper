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
    MainWindow(int num_of_rows,
               int num_of_cols,
               int num_of_bombs,
               std::vector<QPushButton*> b,
               QWidget *parent = 0,
               QLabel* unexposed_label = nullptr);
    ~MainWindow();
    void execute();
private:
    Ui::MainWindow *ui;
    std::vector<QPushButton*> buttons;
    const int num_of_rows = 20;
    const int num_of_cols = 20;
    const int num_of_bombs = 10;
    bool first_move = true; // flag for the 1st move (1st move cannot be a bomb)

public slots:
void clickedSlot();
};
#endif // MAINWINDOW_H
