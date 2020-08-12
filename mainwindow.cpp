#include "ui_mainwindow.h"
#include <QtWidgets>
#include <iostream>
#include <QMainWindow>
#include <QCoreApplication>
#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <vector>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow(int rows,
                       int cols,
                       int bombs,
                       std::vector<QRightClickButton*> b,
                       QWidget *parent,
                       QLabel* unexposed_label,
                       QLabel* unflagged_label,
                       Game* g) :
    QMainWindow(parent),
    ul(unexposed_label),
    unflagged_l(unflagged_label),
    ui(new Ui::MainWindow),
    num_of_cols(cols),
    num_of_rows(rows),
    num_of_bombs(bombs)
{
    buttons = b;
    ui->setupUi(this);
    game = g;
    for(std::size_t i = 0; i < buttons.size(); i++) {
        QString str("X");
        buttons[i]->setText(str);
        str.setNum(i);
        buttons[i]->setAccessibleName(str); // set button name to button number
        const QSize BUTTON_SIZE = QSize(22, 22);
        buttons[i]->setMinimumSize(BUTTON_SIZE);
        QObject::connect(buttons[i], SIGNAL(right()), this, SLOT(rightClick()));
        QObject::connect(buttons[i], SIGNAL(left()), this, SLOT(leftClick()));
    }
    game->ini(unexposed_label, unflagged_label);
}

// flag cell
void MainWindow::rightClick() {
    int row = (((QRightClickButton*)sender())->accessibleName()).toInt() / num_of_cols;
    int col = (((QRightClickButton*)sender())->accessibleName()).toInt() % num_of_cols;
    std::shared_ptr<UserPlay> play = game->from_string(row, col);
    play->is_guess = true;
    game->board->flip_cell(game->board->cells[row][col]);
    std::shared_ptr<UserPlayResult> result = game->board->play_flip(play, game->buttons, num_of_cols);
    if(result->state == GameState::lost || result->state == GameState::won) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Game status");
        msgBox.setText(result->state == GameState::lost ? "Game over. You lost." : "Game over. You won.");
        msgBox.exec();
        exit(0); // close main window
        return;
    }
    if(result->successful_move) {
        game->game_state = result -> state;
    } else {
        std::cout << "Cell (" << play -> row << ", " << play -> col << ") is not possible to flip.\n";
    }
}

void MainWindow::leftClick() {
    int row = (((QPushButton*)sender())->accessibleName()).toInt() / num_of_cols;
    int col = (((QPushButton*)sender())->accessibleName()).toInt() % num_of_cols;
    std::shared_ptr<UserPlay> play = game->from_string(row, col);
    std::shared_ptr<UserPlayResult> result = game->board->play_flip(play, buttons, num_of_cols);
    if(result->state == GameState::lost || result->state == GameState::won) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Game status");
        msgBox.setText(result->state == GameState::lost ? "Game over. You lost." : "Game over. You won.");
        msgBox.exec();
        exit(0); // close main window
        return;
    }
    if(result->successful_move) {
        game->game_state = result -> state;
    } else {
        std::cout << "Cell (" << play -> row << ", " << play -> col << ") is not possible to flip.\n";
    }
    game->print_game_state(this, ul, unflagged_l);
}

MainWindow::~MainWindow()
{
    delete ui;
}
