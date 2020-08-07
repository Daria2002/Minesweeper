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
    MyWidget(int rows, int cols, QWidget *parent = 0) : QGroupBox(parent)
    {
        setTitle("Minesweeper");
        setStyleSheet("QPushButton{background-color: qlineargradient(spread:pad, x1:1, y1:0.682,"
                      "x2:1, y2:0, stop:0.142857 rgba(220, 0, 22, 255),"
                      "stop:0.980296 rgba(216, 74, 73, 255),"
                      "stop:1 rgba(217, 73, 73, 255));"
                      "border:none; color:white;}");
        QGridLayout *grid_layout = new QGridLayout;
        QLabel *unexposed_fields_label = new QLabel;
        unexposed_fields_label->setText("Number of unexposed fields:");
        unexposed_fields_data = new QLabel;
        grid_layout->addWidget(unexposed_fields_label, 0, 0);
        grid_layout->addWidget(unexposed_fields_data, 0, 1);
        QLabel *flagged_bombs_label = new QLabel;
        flagged_bombs_label->setText("Number of unflagged bombs:");
        flagged_bombs_data = new QLabel;
        grid_layout->addWidget(flagged_bombs_label, 1, 0);
        grid_layout->addWidget(flagged_bombs_data, 1, 1);
        for(int i = 0; i < rows; i++)
        {
            for(int j = 2; j <= cols + 1; j++) {
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
    QLabel *unexposed_fields_data;
    QLabel *flagged_bombs_data;
};

int main(int argc, char *argv[])
{
    const int num_of_rows = 10;
    const int num_of_cols = 10;
    const int num_of_bombs = 5;
    std::cout << "Main function starts\n";
    QApplication a(argc, argv);
    MyWidget* widget = new MyWidget(num_of_rows, num_of_cols);
    MainWindow w(num_of_rows, num_of_cols, num_of_bombs, widget->buttons,
                 widget, widget->unexposed_fields_data, widget->flagged_bombs_data);
    widget->show();
    return a.exec();
}

