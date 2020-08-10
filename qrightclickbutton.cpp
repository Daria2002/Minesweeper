#include "qrightclickbutton.h"
#include "minesweeper.h"
#include <vector>
#include <QMessageBox>

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent) {}
QRightClickButton::QRightClickButton(QWidget *parent, Game *g) : QPushButton(parent) {
    game = g;
}
void rightClicked() {

}
void leftClicked() {

}
void QRightClickButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton) {
        emit rightClicked();
    } else {
        emit leftClicked();
    }
    QRightClickButton::mousePressEvent(e);
}
