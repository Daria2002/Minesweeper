#ifndef QRIGHTCLICKBUTTON_H
#define QRIGHTCLICKBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include "minesweeper.h"

class Game;

class QRightClickButton : public QPushButton {
public:
    Game *game;
    QRightClickButton(QWidget *parent, Game *g);
    Q_OBJECT
public:
    explicit QRightClickButton(QWidget *parent = 0);
private slots:
    void mousePressEvent(QMouseEvent *e);
signals:
    void rightClicked();
    void leftClicked();
public slots:
};

#endif // QRIGHTCLICKBUTTON_H
