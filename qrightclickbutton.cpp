#include "qrightclickbutton.h"
#include "minesweeper.h"
#include <vector>
#include <QMessageBox>

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent) {}
QRightClickButton::QRightClickButton(QWidget *parent, Game *g) : QPushButton(parent) {
    game = g;
}
void right() {
    std::cout << "right\n";
}
void left() {
    std::cout << "left\n";
}
void QRightClickButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton) {
        emit right();
    } else {
        emit left();
    }
    QPushButton::mousePressEvent(e);
}
