#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent) {}
QRightClickButton::QRightClickButton(QWidget *parent, Game *g) : QPushButton(parent) {
    game = g;
}
void right() {
}
void left() {
}
void QRightClickButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton) {
        emit right();
    } else {
        emit left();
    }
    QPushButton::mousePressEvent(e);
}
