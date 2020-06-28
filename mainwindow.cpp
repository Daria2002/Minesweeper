#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "minesweeper.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString num_unexposed_str;
    num_unexposed_str.setNum(5);
    ui->num_unexposed->setText(num_unexposed_str);
    Game game(7, 7, 3);
    game.ini();
    game.start();
}

void MainWindow::execute()
{
    Ui::MainWindow *ui;
    ui = new Ui::MainWindow;
    QString num_unexposed_str;
    num_unexposed_str.setNum(1);
    ui->num_unexposed->setText(num_unexposed_str);
}

MainWindow::~MainWindow()
{
    delete ui;
}
