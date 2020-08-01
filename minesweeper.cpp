#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include <string>
#include <QLabel>
#include <sstream>
#include <QMainWindow>
#include <minesweeper.h>
Cell::Cell(int r, int c) : row(r), column(c) {}
void Cell::set_bomb(bool bomb) {
    is_bomb = bomb;
    num = -1;
}
bool Cell::flip() { // returns true if blank or num, otherwise false
    is_exposed = true;
    return !is_bomb;
}
bool Cell::toggle_guess() {
    if(!is_exposed) {
        is_guess = !is_guess;
    }
    return is_guess;
}
std::string Cell::get_real_state() {
    if(is_bomb) return "* ";
    else if(num > 0) return std::to_string(num) + " ";
    return "  "; // blank space and one space distance between consecutive columns
}
std::string Cell::get_revealed_state() {
    if(is_exposed) {
        return get_real_state();
    } else if(is_guess) {
        return "B ";
    }
    return "? ";
}
bool Cell::is_blank() {
    return num == 0 && !is_bomb;
}
void Cell::set_row_and_col(int r, int c) {
    row = r;
    column = c;
}

Board::Board(int r, int c, int b) {
    n_bombs = b;
    n_columns = c;
    n_rows = r;
    ini_board();
    shuffle_board();
    set_numbered_cells();
    num_of_unexposed = n_rows * n_columns - n_bombs;
}
void Board::ini_board() {
    for(int i = 0; i < n_rows; i++) {
        std::vector<std::shared_ptr<Cell>> row_i;
        for(int j = 0; j < n_columns; j++) {
            row_i.push_back(std::make_shared<Cell>(i, j));
        }
        cells.push_back(row_i);
    }
    for(int i = 0; i < n_bombs; i++) {
        int r = i/n_columns;
        int c = (i - r*n_columns) % n_columns;
        bombs.push_back(cells[r][c]);
        bombs[i]->set_bomb(true);
    }
}
void Board::shuffle_board() {
    int n_cells = n_rows * n_columns;
    srand(time(0));
    for(int index1 = 0; index1 < n_cells; index1++) {
        int index2 = index1 + rand() % (n_cells - index1);
        if(index1 != index2) {
            // get cell at index1
            int row1 = index1 / n_columns;
            int column1 = (index1 - row1 * n_columns) % n_columns;
            std::shared_ptr<Cell> cell1 = cells[row1][column1];
            // get cell at index2
            int row2 = index2 / n_columns;
            int column2 = (index2 - row2 * n_columns) % n_columns;
            std::shared_ptr<Cell> cell2 = cells[row2][column2];
            // swap
            cells[row1][column1] = cell2;
            cell2->set_row_and_col(row1, column1);
            cells[row2][column2] = cell1;
            cell1->set_row_and_col(row2, column2);
        }
    }
}
bool Board::in_bounds(int row, int column) {
    return row >= 0 && row < n_rows && column >= 0 && column < n_columns;
}
void Board::set_numbered_cells() {
    std::vector<std::vector<int>> offsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for(std::shared_ptr<Cell>& bomb : bombs) {
        int row = bomb->row;
        int col = bomb->column;
        for(std::vector<int>& offset : offsets) { // for every surranding cell
            int r = row + offset[0]; // make surranding cell row
            int c = col + offset[1]; // make surranding cell column
            if(in_bounds(r, c)) {
                cells[r][c]->num++;
            }
        }
    }
}
void Board::print_board(bool show_real) {
    std::cout << "\n   ";
    for(int i = 0; i < n_columns; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n  ";
    for(int i = 0; i < n_columns; i++) {
        std::cout << "--";
    }
    std::cout << '\n';
    for(int r = 0; r < n_rows; r++) {
        std::cout << r << "| ";
        for(int c = 0; c < n_columns; c++) {
            if(show_real) {
                std::cout << cells[r][c]->get_real_state();
            } else {
                std::cout << cells[r][c]->get_revealed_state();
            }
        }
        std::cout << '\n';
    }
}
bool Board::flip_cell(std::shared_ptr<Cell> cell) {
    if(!cell->is_exposed && !cell->is_guess) {
        cell->flip();
        num_of_unexposed--;
        return true;
    }
    return false;
}
void Board::expand_blank(std::shared_ptr<Cell> cell,
                         std::vector<QPushButton*> buttons,
                         int num_of_cols) {
    std::vector<std::vector<int>> offsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    std::vector<std::shared_ptr<Cell>> to_be_explored;
    to_be_explored.push_back(cell);
    std::shared_ptr<Cell> neighbor;
    std::shared_ptr<Cell> current;
    while (!to_be_explored.empty())
    {
        current = to_be_explored.back();
        to_be_explored.pop_back();
        current->is_exposed = true;
        for(std::vector<int> offset : offsets) {
            int r = current->row + offset[0];
            int c = current->column + offset[1];
            if(in_bounds(r, c)) {
                neighbor = cells[r][c];
                if(neighbor->is_blank() && flip_cell(neighbor)) {
                    QString str = " ";
                    buttons[r * num_of_cols + c]->setText(str);
                    to_be_explored.push_back(neighbor);
                }
                //  if a cell is a bomb neighbour display a number
                if(!neighbor->is_blank()) {
                    QString str;
                    str.setNum(std::stoi(neighbor->get_real_state()));
                    buttons[r * num_of_cols + c]->setText(str);
                }
            }
        }
    }
}

Game::Game(int r, int c, int b) : rows(r), columns(c), bombs(b) {
    game_state = GameState::playing;
}
bool Game::ini(QLabel* unexposed_label) {
    if(board == nullptr) {
        board = std::make_shared<Board>(rows, columns, bombs);
        board->print_board(true); // show real board
        QString num_unexposed_str;
        num_unexposed_str.setNum(board->num_of_unexposed);
        unexposed_label->setText(num_unexposed_str);
        return true;
    }
    return false; // already initialized
}
bool Game::start(QMainWindow* w, QLabel* unexposed_label) {
    if(board == nullptr) {
        ini(unexposed_label);
    }
    return play_game(w, unexposed_label);
}
void Game::print_game_state(QMainWindow* w, QLabel* unexposed_label) {
    if(game_state == GameState::lost) {
        board->print_board(true);
        std::cout << "FAIL\n";
    } else if(game_state == GameState::won) {
        board->print_board(true);
        std::cout << "WIN\n";
    } else {
        QString num_unexposed_str;
        num_unexposed_str.setNum(board->num_of_unexposed);
        unexposed_label->setText(num_unexposed_str);
        std::cout << "Number of unexposed elements: " << board->num_of_unexposed << '\n';
        board->print_board(false);
    }
}

UserPlayResult::UserPlayResult(bool sm, GameState s) : successful_move(sm), state(s) {}

void split(const std::string& str, std::vector<std::string>& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

UserPlay::UserPlay(int r, int c, bool guess) : row(r), col(c), is_guess(guess) {}

static std::shared_ptr<UserPlay> from_string(std::string input) {
    bool isguess = false;
    if(input.size() > 0 && input[0] == 'B') {
        isguess = true;
        input = input.substr(2);
    }
    std::vector<std::string> parts;
    split(input, parts, ' ');
    int r = std::stoi(parts[0]);
    int c = std::stoi(parts[1]);
    return std::make_shared<UserPlay>(r, c, isguess);
}

std::shared_ptr<UserPlay> Game::from_string(int r, int c) {
    bool isguess = false;
    return std::make_shared<UserPlay>(r, c, isguess);
}

std::shared_ptr<UserPlayResult> Board::play_flip(std::shared_ptr<UserPlay> play,
                                                 std::vector<QPushButton*> buttons,
                                                 int num_of_cols) {
    if(in_bounds(play->row, play->col) == false) {
        return std::make_shared<UserPlayResult>(false, GameState::playing);
    }
    std::shared_ptr<Cell> cell = cells[play->row][play->col];
    if(play->is_guess) {
        bool guess_res = cell->toggle_guess();
        return std::make_shared<UserPlayResult>(guess_res, GameState::playing);
    }
    bool res = flip_cell(cell);
    if(cell->is_bomb) {
        QString str = "*";
        buttons[play->row * num_of_cols + play->col]->setText(str);
        return std::make_shared<UserPlayResult>(res, GameState::lost);
    } else if(cell->is_blank()) { // set text to " " because it's a blank cell
        QString str = " ";
        buttons[play->row * num_of_cols + play->col]->setText(str);
        expand_blank(cell, buttons, num_of_cols);
    } else { // if num
        QString str = QString::fromUtf8(cell->get_real_state().data());
        buttons[play->row * num_of_cols + play->col]->setText(str);
    }
    if(num_of_unexposed == 0) {
        // display bombs because player won
        for(std::shared_ptr<Cell> bomb : bombs) {
            QString str = "*";
            buttons[bomb->row * num_of_cols + bomb->column]->setText(str);
        }
        return std::make_shared<UserPlayResult>(res, GameState::won);
    }
    return std::make_shared<UserPlayResult>(res, GameState::playing);
}

bool Game::play_game(QMainWindow* w, QLabel* unexposed_label) {
//    print_game_state();
//    std::string input;
//    while (game_state == GameState::playing)
//    {
//        std::getline(std::cin, input);
//        if(input == "exit") {
//            return false;
//        }
//        std::shared_ptr<UserPlay> play = from_string(input);
//        if(play == nullptr) {
//            continue;
//        }
//        std::shared_ptr<UserPlayResult> result = board->play_flip(play);
//        if(result->successful_move) {
//            game_state = result->state;
//        } else {
//            std::cout << "Cell (" << play->row << ", " << play->col << ") is not possible to flip.\n";
//        }
        print_game_state(w, unexposed_label);
//    }
    return true;
}
