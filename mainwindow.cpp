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
#include "minesweeper.h"
#include <mainwindow.h>

MainWindow::MainWindow(int rows,
                       int cols,
                       int bombs,
                       std::vector<QPushButton*> b,
                       QWidget *parent,
                       QLabel* unexposed_label) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ul(unexposed_label),
    num_of_cols(cols),
    num_of_rows(rows),
    num_of_bombs(bombs)
{
    buttons = b;
    ui->setupUi(this);
    game = new Game(num_of_rows, num_of_cols, num_of_bombs);
    for(int i = 0; i < buttons.size(); i++) {
        QString str("X");
        buttons[i]->setText(str);
        str.setNum(i);
        buttons[i]->setAccessibleName(str); // set button name to button number
        const QSize BUTTON_SIZE = QSize(22, 22);
        buttons[i]->setMinimumSize(BUTTON_SIZE);
        QObject::connect(buttons[i], SIGNAL(released()), this, SLOT(clickedSlot()));
    }
    game->ini(unexposed_label);
    game->start(this, unexposed_label);
}

void MainWindow::clickedSlot()
{
    int row = (((QPushButton*)sender())->accessibleName()).toInt() / num_of_cols;
    int col = (((QPushButton*)sender())->accessibleName()).toInt() % num_of_cols;
    if(first_move) {
        first_move = false;
        // shuffle board until first move is not a bomb
        while(game->board->cells[row][col]->is_bomb) {
            game->board->shuffle_board();
        }
    }
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
    game->print_game_state(this, ul);
}

MainWindow::~MainWindow()
{
    delete ui;
}
