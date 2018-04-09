#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Board;

class Random{

public:
    Random();
    int getRandomMove(Board* board, bool whiteTeam, int move[4]);

private:
    int piecesInRow(Board* board, bool whiteTeam, int row);
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};

#endif // RANDOM_H