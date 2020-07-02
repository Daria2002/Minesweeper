#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.cpp"
#include <QtWidgets>
#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include <QtWidgets>
#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent, QLabel* unexposed_label, std::vector<QPushButton*> buttons) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::cout << "Main window constructor\n";
    Game game(7, 7, 3);
    game.ini(unexposed_label);
    game.start(this, unexposed_label);
}

MainWindow::~MainWindow()
{
    delete ui;
}
