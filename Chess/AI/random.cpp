#include "random.h"

#include <iostream>

Random::Random() {
    mt = std::mt19937(rd());
    dist = std::uniform_int_distribution<int>(0,7);
}

int Random::getRandomMove(Controller* controller, bool whiteTeam, int move[4]) {
    int col, row, nPiecesInRow;
    QVector<QPoint> posMoves;

    QVector<QPoint> failedLocations;

    do {
        do {
            row = dist(mt);
            nPiecesInRow = piecesInRow(controller, whiteTeam, row);

            if(nPiecesInRow == 0){
                for (int i = 0; i < 8; ++i) {
                    if(!failedLocations.contains(QPoint(i,row))){
                        failedLocations.append(QPoint(i,row));
                    }
                }
            }

        } while (nPiecesInRow == 0);

        if (nPiecesInRow == 1) {
            for (int x = 0; x < 8; ++x) {
                if (whiteTeam && controller->getBoard()->getPiece(x, row) > 0) {
                    move[0] = x;
                    move[1] = row;
                } else if (!whiteTeam && controller->getBoard()->getPiece(x, row) < 0) {
                    move[0] = x;
                    move[1] = row;
                } else{
                    if(!failedLocations.contains(QPoint(x,row))){
                        failedLocations.append(QPoint(x,row));
                    }
                }
            }
        } else if (nPiecesInRow > 1) {
            do {
                col = dist(mt);

                if((whiteTeam && controller->getBoard()->getPiece(col, row) < 0) || (!whiteTeam && controller->getBoard()->getPiece(col, row) > 0)){
                    if(!failedLocations.contains(QPoint(col,row))){
                        failedLocations.append(QPoint(col,row));
                    }
                }
            } while (!((whiteTeam && controller->getBoard()->getPiece(col, row) > 0) ||
                       (!whiteTeam && controller->getBoard()->getPiece(col, row) < 0)));
            move[0] = col;
            move[1] = row;
        }

        posMoves = controller->getBoard()->getMoves(move[0], move[1]);

    }while (posMoves.length() == 0 || failedLocations.length() == 64);

    std::uniform_int_distribution<int> moveDist(0,posMoves.length()-1);
    int loc = moveDist(mt);

    if(posMoves.length() == 0){
        return 0;
    }else{

        std::cout << "Loc: " << loc << ", Len of Vector: " << posMoves.length() << std::endl;

        move[2] = posMoves[loc].x();
        move[3] = posMoves[loc].y();
        return 1;
    }
}

int Random::piecesInRow(Controller *controller, bool whiteTeam, int row) {
    int nPieces = 0;

    for (int x = 0; x < 8; ++x) {
        if(whiteTeam && controller->getBoard()->getPiece(x,row) > 0){
            nPieces++;
        }else if(!whiteTeam && controller->getBoard()->getPiece(x,row) < 0){
            nPieces++;
        }
    }

    return nPieces;
}
