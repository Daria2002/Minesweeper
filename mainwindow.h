#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QLabel* unexposed_label = nullptr);
    ~MainWindow();
    void execute();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
