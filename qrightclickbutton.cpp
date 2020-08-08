#include "qrightclickbutton.h"

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent) {}
void QRightClickButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton) {
        // flag a bomb
    } else {
        // open a field
    }
}
