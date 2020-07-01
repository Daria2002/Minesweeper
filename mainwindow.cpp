#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.cpp"
#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent, QLabel* unexposed_label) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game game(7, 7, 3);
    game.ini(unexposed_label);
    game.start(this, unexposed_label);
}

MainWindow::~MainWindow()
{
    delete ui;
}
