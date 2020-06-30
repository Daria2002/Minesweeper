#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.cpp"
#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game game(7, 7, 3);
    game.ini();
    game.start(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
