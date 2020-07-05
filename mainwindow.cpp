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
    ui(new Ui::MainWindow)
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
    QMessageBox msgBox;
    msgBox.setWindowTitle("MessageBox Title");
    msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
