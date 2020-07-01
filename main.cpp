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
        QLabel *label_text = new QLabel;
        label_text->setText("Number of unexposed fields:");
        QLabel *label_data = new QLabel;
        label_data->setText("Number");
        grid_layout->addWidget(label_text, 0, 0);
        grid_layout->addWidget(label_data, 0, 1);
        int size = 7;
        for(int i = 0; i < size; i++)
        {
            for(int j = 2; j <= size + 1; j++) {
                QPushButton *button = new QPushButton;
                button->setFixedSize(50, 50);
                button->setText("");
                grid_layout->addWidget(button, i, j);
            }
        }
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

