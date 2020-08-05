#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

class Game;
class Board;
class Cell;
class UserPlay;
class UserPlayResult;

// blank cell is a type of number cell where the number is 0
class Cell {
    public:
        Cell(int r, int c);
        Cell() = default;
        void set_bomb(bool bomb);
        bool flip();
        bool toggle_guess();
        std::string get_real_state();
        std::string get_revealed_state();
        bool is_blank();
        void set_row_and_col(int r, int c);
        int column, row;
        bool is_exposed = false;
        bool is_guess = false;
        int num = 0;
        bool is_bomb = false;
};

class Board {
    public:
        int n_rows, n_columns, n_bombs, num_of_unexposed;
        Board() = default;
        Board(int r, int c, int b);
        void ini_board();
        void shuffle_board();
        bool in_bounds(int row, int column);
        void set_numbered_cells();
        void print_board(bool show_real);
        bool flip_cell(std::shared_ptr<Cell> cell);
        void expand_blank(std::shared_ptr<Cell> cell,
                          std::vector<QPushButton*> buttons,
                          int num_of_cols);
        std::shared_ptr<Cell> get_cell_at_location(std::shared_ptr<UserPlay>);
        std::shared_ptr<UserPlayResult> play_flip(std::shared_ptr<UserPlay>,
                                                  std::vector<QPushButton*> buttons,
                                                  int num_of_cols);
        std::vector<std::vector<std::shared_ptr<Cell>>> cells;
        std::vector<std::shared_ptr<Cell>> bombs;
};

enum GameState {
    won, lost, playing
};

class Game {
    public:
        int rows, columns, bombs;
        std::shared_ptr<Board> board;
        GameState game_state;
        Game() = default;
        Game(int r, int c, int b);
        bool ini(QLabel* unexposed_label);
        void print_game_state(QMainWindow* w, QLabel* unexposed_label);
        std::shared_ptr<UserPlay> from_string(int r, int c);
};

class UserPlayResult {
    public:
        UserPlayResult(bool sm, GameState s);
        bool successful_move;
        GameState state;
};

class UserPlay : public std::enable_shared_from_this<UserPlay> {
    public:
        int row, col;
        bool is_guess;
        UserPlay() = default;
        UserPlay(int r, int c, bool guess);
};


#endif // MINESWEEPER_H
