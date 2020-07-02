#include "mainwindow.h"
#include <QtWidgets>
#include <QMainWindow>
#include <QtGui>
#include <QApplication>
#include <QGroupBox>
#include <QLayout>
#include <iostream>
#include <QPushButton>
#include <vector>

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
        label_data = new QLabel;
        grid_layout->addWidget(label_text, 0, 0);
        grid_layout->addWidget(label_data, 0, 1);
        int size = 7;
        for(int i = 0; i < size; i++)
        {
            for(int j = 2; j <= size + 1; j++) {
                QPushButton *button = new QPushButton;
                button->setFixedSize(50, 50);
                button->setText("");
                buttons.push_back(button);
                grid_layout->addWidget(button, i, j);
            }
        }
        setLayout(grid_layout);
    }
    std::vector<QPushButton*> buttons;
    QLabel *label_data;
};

int main(int argc, char *argv[])
{
    std::cout << "Main function starts\n";
    QApplication a(argc, argv);
    MyWidget* widget = new MyWidget();
    MainWindow w(widget, widget -> label_data, widget -> buttons);
    widget -> show();
    return a.exec();
}

