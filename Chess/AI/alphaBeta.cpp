#include "alphaBeta.h"
#include "Controller/controller.h"

AlphaBeta::AlphaBeta(Controller* controller) {
    this->controller = controller;

}

QVector<int> AlphaBeta::findMove(bool whiteTeam) {

    QVector<int> move = minimaxRoot(4, whiteTeam);

    return move;
}

char AlphaBeta::findUpgrade() {
    return randomMove.getRandomUpgrade();
}

QVector<QVector<int>> AlphaBeta::getAllMoves(bool whiteTeam) {
    QVector<QVector<int>> allPossibleMoves;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(controller->getBoard()->getPiece(x,y) < 0 && !whiteTeam){
                QVector<QPoint> moves = controller->getMoves(x,y);

                for(QPoint point: moves){
                    QVector<int> move;
                    move.append(x);
                    move.append(y);

                    move.append(point.x());
                    move.append(point.y());

                    allPossibleMoves.append(move);
                }
            }else if(controller->getBoard()->getPiece(x,y) > 0 && whiteTeam){
                QVector<QPoint> moves = controller->getMoves(x,y);

                for(QPoint point: moves) {
                    QVector<int> move;
                    move.append(x);
                    move.append(y);

                    move.append(point.x());
                    move.append(point.y());

                    allPossibleMoves.append(move);
                }
            }
        }
    }

    return allPossibleMoves;
}

int AlphaBeta::evaluateBoard(int** board) {

    int score = 0;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            score += map.getItem(board[y][x]);
        }
    }
    return score;

}

int AlphaBeta::minimax(int depth,int alpha, int beta, bool whiteTeam) {
    if(depth == 0){
        return evaluateBoard(controller->getBoard()->getBoard());
    }

    QVector<QVector<int>> allMoves = getAllMoves(whiteTeam);

    if(whiteTeam){
        int bestScore = INT_MIN;

        for(QVector<int> move: allMoves){

            int temp = controller->getBoard()->getPiece(move[2], move[3]);
            controller->getBoard()->setPiece(move[2],move[3], controller->getBoard()->getPiece(move[0], move[1]));
            controller->getBoard()->setPiece(move[0],move[1], 0);

            bestScore = std::max(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            controller->getBoard()->setPiece(move[0],move[1], controller->getBoard()->getPiece(move[2], move[3]));
            controller->getBoard()->setPiece(move[2],move[3], temp);

            alpha = std::max(alpha, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    } else{
        int bestScore = INT_MAX;

        for(QVector<int> move: allMoves){
            int temp = controller->getBoard()->getPiece(move[2], move[3]);
            controller->getBoard()->setPiece(move[2],move[3], controller->getBoard()->getPiece(move[0], move[1]));
            controller->getBoard()->setPiece(move[0],move[1], 0);

            bestScore = std::min(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            controller->getBoard()->setPiece(move[0],move[1], controller->getBoard()->getPiece(move[2], move[3]));
            controller->getBoard()->setPiece(move[2],move[3], temp);

            beta = std::min(beta, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    }

}

QVector<int> AlphaBeta::minimaxRoot(int depth, bool whiteTeam) {
    QVector<QVector<int>> allMoves = getAllMoves(whiteTeam);
    int bestScore;
    QVector<int> bestMove;


    if(whiteTeam){
        bestScore = INT_MIN;
    }else{
        bestScore = INT_MAX;
    }

    for(QVector<int> move: allMoves){
        int temp = controller->getBoard()->getPiece(move[2], move[3]);
        controller->getBoard()->setPiece(move[2],move[3], controller->getBoard()->getPiece(move[0], move[1]));
        controller->getBoard()->setPiece(move[0],move[1], 0);

        int score = minimax(depth, INT_MIN, INT_MAX,  whiteTeam);

        controller->getBoard()->setPiece(move[0],move[1], controller->getBoard()->getPiece(move[2], move[3]));
        controller->getBoard()->setPiece(move[2],move[3], temp);

        if(whiteTeam){
            if(score > bestScore){
                bestScore = score;
                bestMove = move;
            }
        }else{
            if(score < bestScore){
                bestScore = score;
                bestMove = move;
            }
        }
    }

    return bestMove;
}