#include "qrightclickbutton.h"
#include "minesweeper.h"
#include <vector>
#include <QMessageBox>

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent) {}
QRightClickButton::QRightClickButton(QWidget *parent, Game *g) : QPushButton(parent) {
    game = g;
}
void QRightClickButton::mousePressEvent(QMouseEvent *e) {
    int num_of_cols = game->columns;
    std::cout << "Position: x = " << e->pos().x() << ", y = " << e->pos().y() << '\n';
    if(e->button() == Qt::RightButton) {
        // flag a bomb
        int row = (((QPushButton*)sender())->accessibleName()).toInt() / num_of_cols;
        int col = (((QPushButton*)sender())->accessibleName()).toInt() % num_of_cols;
        std::shared_ptr<UserPlay> play = game->from_string(row, col);
        play->is_guess = true;
        game->board->flip_cell(game->board->cells[row][col]);
        std::shared_ptr<UserPlayResult> result = game->board->play_flip(play, game->buttons, num_of_cols);
        if(result->state == GameState::lost || result->state == GameState::won) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Game status");
            msgBox.setText(result->state == GameState::lost ? "Game over. You lost." : "Game over. You won.");
            msgBox.exec();
            exit(0); // close main window
            return;
        }
        if(result->successful_move) {
            game->game_state = result -> state;
        } else {
            std::cout << "Cell (" << play -> row << ", " << play -> col << ") is not possible to flip.\n";
        }
    } else {
        // open a field, left click
        int row = (((QPushButton*)sender())->accessibleName()).toInt() / num_of_cols;
        int col = (((QPushButton*)sender())->accessibleName()).toInt() % num_of_cols;
        std::shared_ptr<UserPlay> play = game->from_string(row, col);
        std::shared_ptr<UserPlayResult> result = game->board->play_flip(play, game->buttons, num_of_cols);
        if(result->state == GameState::lost || result->state == GameState::won) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Game status");
            msgBox.setText(result->state == GameState::lost ? "Game over. You lost." : "Game over. You won.");
            msgBox.exec();
            exit(0); // close main window
            return;
        }
        if(result->successful_move) {
            game->game_state = result -> state;
        } else {
            std::cout << "Cell (" << play -> row << ", " << play -> col << ") is not possible to flip.\n";
        }
    }
}
