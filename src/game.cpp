#include "game.h"
using namespace TTT;

GameView::GameView() {
    int a;
    int mode;
    std::cout << "Choose game area size (3-5)\n";
    std::cin >> a;
    while (a < 3 || a > 5) {
        std::cin >> a;
    }
    std::cout << "Choose game mode (1-3)\n1 - pvp\n2 - pvc\n3 - cvc\n";
    std::cin >> mode;
    while (mode < 1 || mode > 3) {
        std::cin >> mode;
    }
    s_ = a;
    mode_ = mode;
    field_ = new char*[s_]();
    for (auto i = 0; i < s_; i++) {
        field_[i] = new char[s_]();
    }
    InitField();
}

GameView::~GameView() {
    if (field_ != nullptr) {
        for (int i = 0; i < s_; i++) {
            delete[] field_[i];
        }
        delete[] field_;
    }
}

bool GameView::SetField(char** other, int size) {
    if (s_ == size) {
        for (int i = 0; i < s_; i++) {
            for (int j = 0; j < s_; j++) {
                field_[i][j] = other[i][j];
            }
        }
        return true;
    }
    return false;
}

void GameView::InitField() {
    for (int i = 0; i < s_; i++) {
        for (int j = 0; j < s_; j++) {
            field_[i][j] = '*';
        }
    }
}

void GameView::ShowField() {
    std::cout << "   ";
    for (int i = 0; i < s_; i++) {
        std::cout << i + 1 << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < s_; i++) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < s_; j++) {
            std::cout << field_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool GameView::WinCheck() {
    char row, col, diag1, diag2;
    int countrow, countcol, countdiag1 = 0, countdiag2 = 0;
    diag1 = field_[0][0];
    diag2 = field_[s_ - 1][0];
    for (int i = 0; i < s_; i++) {
        countrow = 0;
        countcol = 0;
        countdiag1 = 0;
        countdiag2 = 0;
        row = field_[i][0];
        col = field_[0][i];
        for (int j = 0; j < s_; j++) {
            if (row == field_[i][j] && field_[i][j] != '*') {
                countrow++;
            }
            if (col == field_[j][i] && field_[j][i] != '*') {
                countcol++;
            }
            if (diag1 == field_[j][j] && field_[j][j] != '*') {
                countdiag1++;
            }
            if (diag2 == field_[s_ - 1 - j][j] &&
                field_[s_ - 1 - j][j] != '*') {
                countdiag2++;
            }
            if (countrow == s_ || countcol == s_ || countdiag1 == s_ ||
                countdiag2 == s_) {
                return true;
            }
        }
    }
    return false;
}

bool GameView::TieCheck() {
    for (int i = 0; i < s_; i++) {
        for (int j = 0; j < s_; j++) {
            if (field_[i][j] == '*') {
                return false;
            }
        }
    }
    return true;
}

bool GameView::SetChar(int row, int col, char* c) {
    if (row > 0 && row <= s_ && col > 0 && col <= s_) {
        if (field_[row - 1][col - 1] == '*') {
            field_[row - 1][col - 1] = *c;
            return true;
        }
    }
    return false;
}

void GameView::MakeATurn(char* c) {
    int row, col;
    bool free = false;
    std::cout << c << " turn\n";
    std::cout << "Enter row & col to set\n";
    std::cin >> row;
    std::cin >> col;
    free = SetChar(row, col, c);
    if (!free) {
        ShowField();
        MakeATurn(c);
    } else {
        if (*c == 'X') {
            *c = 'O';
        } else {
            *c = 'X';
        }
    }
}

void GameView::NewGame() {
    char curr = 'X';
    std::cout << "Randomizing the turn\n";
    sleep(1);
    std::srand(std::time(nullptr));
    if (std::rand() % 2 == 0) {
        curr = 'O';
    }
    ShowField();
    sleep(1);
    if (mode_ == 1) {
        while (!WinCheck() && !TieCheck()) {
            MakeATurn(&curr);
            ShowField();
        }
    } else if (mode_ == 2) {
        AI comp('O');
        while (!WinCheck() && !TieCheck()) {
            if (curr == 'X') {
                MakeATurn(&curr);
            } else {
                std::cout << curr << " turn\n";
                sleep(1);
                std::pair<int, int> coord = comp.MakeDecision(field_, s_);
                int row = coord.first + 1;
                int col = coord.second + 1;
                SetChar(row, col, &curr);
                curr = 'X';
            }
            ShowField();
        }
    } else if (mode_ == 3) {
        AI comp('O');
        AI comp1('X');
        while (!WinCheck() && !TieCheck()) {
            std::cout << curr << " turn\n";
            if (curr == 'X') {
                std::pair<int, int> coord = comp1.MakeDecision(field_, s_);
                int row = coord.first + 1;
                int col = coord.second + 1;
                SetChar(row, col, &curr);
                curr = 'O';
            } else {
                std::pair<int, int> coord = comp.MakeDecision(field_, s_);
                int row = coord.first + 1;
                int col = coord.second + 1;
                SetChar(row, col, &curr);
                curr = 'X';
            }
            ShowField();
            sleep(0.5);
        }
    }
    if (WinCheck()) {
        char winner;
        if (curr == 'X') {
            winner = 'O';
        } else {
            winner = 'X';
        }
        std::cout << winner << " won!\nWanna play again? (y/n)\n";
    } else {
        std::cout << "Tie!\nWanna play again? (y/n)\n";
    }
    char ans;
    std::cin >> ans;
    if (ans == 'y') {
        InitField();
        NewGame();
    } else {
        std::cout << "Thank you, bye =)\n";
    }
}

int GameView::GetSize() { return s_; }

char** GameView::GetField() { return field_; }
