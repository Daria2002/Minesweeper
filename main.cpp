#include "mainwindow.h"
#include <QtWidgets>
#include <QMainWindow>
#include <QtGui>
#include <QApplication>
#include <QGroupBox>
#include <QLayout>
#include <QPushButton>

class MyWidget : public QGroupBox
{
public:
    MyWidget(QWidget *parent = 0) : QGroupBox(parent)
    {
        setTitle("Minesweeper");
        setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:1, y1:0.682,"
                      "x2:1, y2:0, stop:0.142857 rgba(220, 0, 22, 255),"
                      "stop:0.980296 rgba(216, 74, 73, 255),"
                      "stop:1 rgba(217, 73, 73, 255));"
                      "border:none; color:white;}");
        QGridLayout *grid_layout = new QGridLayout;
        int size = 7;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++) {
                QPushButton *button = new QPushButton;
                button->setFixedSize(80, 80);
                button->setText("");
                grid_layout->addWidget(button, j, i);
            }
        }
        grid_layout->setAlignment(Qt::AlignCenter);
        grid_layout->setSpacing(1);
        setLayout(grid_layout);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget widget;
    widget.resize(800, 200);
    widget.show();
    return a.exec();
}

