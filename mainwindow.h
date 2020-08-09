#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <vector>
#include "minesweeper.h"
#include "qrightclickbutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Game* game;
    QLabel* ul;
    QLabel* unflagged_l;
    MainWindow(int r,
               int c,
               int bombs,
               std::vector<QRightClickButton*> b,
               QWidget *parent = 0,
               QLabel* unexposed_label = nullptr,
               QLabel* unflagged_label = nullptr,
               Game* g = nullptr);
    ~MainWindow();
    void execute();
    void rightClick();
private:
    Ui::MainWindow *ui;
    std::vector<QRightClickButton*> buttons;
    int num_of_cols;
    int num_of_rows;
    int num_of_bombs;
    bool first_move = true; // flag for the 1st move (1st move cannot be a bomb)

public slots:
void leftClick();
};
#endif // MAINWINDOW_H
