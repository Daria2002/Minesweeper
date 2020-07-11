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

MainWindow::MainWindow(QWidget *parent, QLabel* unexposed_label, std::vector<QPushButton*> buttons) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ul(unexposed_label)
{
    ui->setupUi(this);
    std::cout << "Main window constructor\n";
    game = new Game(7, 7, 3);
    for(int i = 0; i < buttons.size(); i++) {
        QString str;
        str.setNum(i);
        buttons[i]->setText(str);
        QObject::connect(buttons[i], SIGNAL(released()), this, SLOT(clickedSlot()));
    }
    game->ini(unexposed_label);
    game->start(this, unexposed_label);
}

void MainWindow::clickedSlot()
{
    int row = (((QPushButton*)sender())->text()).toInt() / 7;
    int col = (((QPushButton*)sender())->text()).toInt() % 7;
    std::shared_ptr<UserPlay> play = game -> from_string(row, col);
    std::shared_ptr<UserPlayResult> result = game -> board -> play_flip(play);
    if(result -> successful_move) {
        game -> game_state = result -> state;
    } else {
        std::cout << "Cell (" << play -> row << ", " << play -> col << ") is not possible to flip.\n";
    }
    game -> print_game_state(this, ul);
    /*
    QMessageBox msgBox;
    msgBox.setWindowTitle("MessageBox Title");
    msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
    msgBox.exec();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
