#ifndef SRC_VIEW_H_
#define SRC_VIEW_H_
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "logic.h"

namespace TTT {
class GameView {
 public:
    GameView();
    GameView(int size);
    ~GameView();
    void NewGame();
    int GetSize();
    char** GetField();
    bool SetField(char** other, int size);
    bool WinCheck();
    bool TieCheck();

 private:
    void ShowField();
    bool SetChar(int row, int col, char* c);
    void InitField();
    void MakeATurn(char* c);

 private:
    int s_, mode_;
    char** field_;
};
}  // namespace TTT

#endif  // SRC_VIEW_H_
