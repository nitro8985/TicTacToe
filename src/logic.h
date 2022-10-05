#ifndef SRC_LOGIC_H_
#define SRC_LOGIC_H_
#include <cmath>

#include "game.h"

namespace TTT {
class AI {
 public:
    AI(char c) : own_(c) {
        if (own_ == 'X') {
            opp_ = 'O';
        } else {
            opp_ = 'X';
        }
    }
    ~AI() {}
    std::pair<int, int> MakeDecision(char** field, int size);

 private:
    int Minimax(char** field, int size, int depth, bool isMax);
    int EvaluateCurrState(char** field, int size);
    bool MoveRemains(char** field, int size);

 private:
    char own_, opp_;
};
}  // namespace TTT

#endif  // SRC_LOGIC_H_