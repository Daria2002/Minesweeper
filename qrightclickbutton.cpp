#include "qrightclickbutton.h"
#include "minesweeper.h"

QRightClickButton::QRightClickButton(QWidget *parent) : QPushButton(parent) {}
QRightClickButton::QRightClickButton(QWidget *parent, Game *g) : QPushButton(parent) {
    game = g;
}
void QRightClickButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton) {
        // flag a bomb
        int row = (((QPushButton*)sender())->accessibleName()).toInt() / num_of_cols;
        int col = (((QPushButton*)sender())->accessibleName()).toInt() % num_of_cols;
        std::shared_ptr<UserPlay> play = game->from_string(row, col);
        play->is_guess = true;
        game->board->flip_cell(game->board->cells[row][col]);
        std::shared_ptr<UserPlayResult> result = game->board->play_flip(play, buttons, num_of_cols);
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
        game->print_game_state(this, ul, unflagged_l);
    } else {
        // open a field, left click
        int row = (((QPushButton*)sender())->accessibleName()).toInt() / num_of_cols;
        int col = (((QPushButton*)sender())->accessibleName()).toInt() % num_of_cols;
        if(first_move) {
            first_move = false;
            // shuffle board until first move is not a bomb
            while(game->board->cells[row][col]->is_bomb) {
                game->board->shuffle_board();
            }
        }
        std::shared_ptr<UserPlay> play = game->from_string(row, col);
        std::shared_ptr<UserPlayResult> result = game->board->play_flip(play, buttons, num_of_cols);
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
        game->print_game_state(this, ul, unflagged_l);
    }
}
