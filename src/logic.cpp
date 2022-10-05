#include "logic.h"

using namespace TTT;

bool AI::MoveRemains(char** field, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (field[i][j] == '*') {
                return true;
            }
    return false;
}

int AI::EvaluateCurrState(char** field, int size) {
    for (int row = 0; row < size; row++) {
        int counter = 0;
        char curr = field[row][0];
        for (int i = 0; i < size; i++) {
            if (field[row][i] == curr) {
                counter++;
            }
        }
        if (counter == size) {
            if (curr == own_) {
                return +10;
            } else if (curr == opp_) {
                return -10;
            }
        }
    }
    for (int col = 0; col < size; col++) {
        int counter = 0;
        char curr = field[0][col];
        for (int i = 0; i < size; i++) {
            if (field[i][col] == curr) {
                counter++;
            }
        }
        if (counter == size) {
            if (curr == own_) {
                return +10;
            } else if (curr == opp_) {
                return -10;
            }
        }
    }
    char d1 = field[0][0], d2 = field[size - 1][0];
    int c1 = 0, c2 = 0;
    for (int i = 0; i < size; i++) {
        if (field[i][i] == d1) {
            c1++;
        }
    }
    if (c1 == size) {
        if (d1 == own_) {
            return +10;
        } else if (d1 == opp_) {
            return -10;
        }
    }
    for (int i = 0; i < size; i++) {
        if (field[size - 1 - i][i] == d2) {
            c2++;
        }
    }
    if (c2 == size) {
        if (d2 == own_) {
            return +10;
        } else if (d2 == opp_) {
            return -10;
        }
    }
    return 0;
}

int AI::Minimax(char** field, int size, int depth, bool isMax) {
    int curr_score = EvaluateCurrState(field, size);
    if (curr_score == +10) {
        return curr_score;
    }
    if (curr_score == -10) {
        return curr_score;
    }
    if (!MoveRemains(field, size) || depth == 0) {
        return 0;
    }
    if (isMax) {
        int best_score = -1000;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (field[i][j] == '*') {
                    field[i][j] = own_;
                    best_score = std::fmax(
                        best_score, Minimax(field, size, depth - 1, !isMax));
                    field[i][j] = '*';
                }
            }
        }
        return best_score;
    } else {
        int best_score = 1000;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (field[i][j] == '*') {
                    field[i][j] = opp_;

                    best_score = std::fmin(
                        best_score, Minimax(field, size, depth - 1, !isMax));

                    field[i][j] = '*';
                }
            }
        }
        return best_score;
    }
}

std::pair<int, int> AI::MakeDecision(char** field, int size) {
    int depth = size > 3 ? 3 : 5;
    int best_score = -1000;
    std::pair<int, int> best_cell;
    best_cell = std::make_pair(-1, -1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (field[i][j] == '*') {
                field[i][j] = own_;
                int curr_move_score = Minimax(field, size, depth, false);
                field[i][j] = '*';
                if (curr_move_score > best_score) {
                    best_cell = std::make_pair(i, j);
                    best_score = curr_move_score;
                }
            }
        }
    }
    return best_cell;
}
