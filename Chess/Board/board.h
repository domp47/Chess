#ifndef BOARD_H
#define BOARD_H

class Board{
public:
    Board();
    int getPiece(int x, int y);

private:
    int** board;
};

#endif //BOARD_H