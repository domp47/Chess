#include "alphaBeta.h"
#include "Controller/controller.h"

AlphaBeta::AlphaBeta(Controller* controller) {
    this->controller = controller;

}

QVector<int> AlphaBeta::findMove(bool whiteTeam) {

    QVector<int> move = minimaxRoot(3, controller->getBoard()->getBoard(), whiteTeam);

    return move;
}

char AlphaBeta::findUpgrade() {
    return randomMove.getRandomUpgrade();
}

QVector<QVector<int>> AlphaBeta::getAllMoves(int** board, bool whiteTeam) {
    QVector<QVector<int>> allPossibleMoves;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(board[y][x] < 0 && !whiteTeam){
                QVector<QPoint> moves = controller->getMoves(board, x,y);

                for(QPoint point: moves){
                    QVector<int> move;
                    move.append(x);
                    move.append(y);

                    move.append(point.x());
                    move.append(point.y());

                    allPossibleMoves.append(move);
                }
            }else if(controller->getBoard()->getPiece(x,y) > 0 && whiteTeam){
                QVector<QPoint> moves = controller->getMoves(board, x,y);

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

int AlphaBeta::minimax(int depth,int alpha, int beta,  int** board, bool whiteTeam) {
    if(depth == 0){
        return evaluateBoard(board);
    }

    QVector<QVector<int>> allMoves = getAllMoves(board,whiteTeam);

    if(whiteTeam){
        int bestScore = INT_MIN;

        for(QVector<int> move: allMoves){
            int temp = board[move[3]][move[2]];
            board[move[3]][move[2]] = board[move[1]][move[0]];
            board[move[1]][move[0]] = 0;

            bestScore = std::max(bestScore, minimax(depth-1,alpha, beta, board,!whiteTeam));

            board[move[1]][move[0]] = board[move[3]][move[2]];
            board[move[3]][move[2]] = temp;

            alpha = std::max(alpha, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    } else{
        int bestScore = INT_MAX;

        for(QVector<int> move: allMoves){
            int temp = board[move[3]][move[2]];
            board[move[3]][move[2]] = board[move[1]][move[0]];
            board[move[1]][move[0]] = 0;

            bestScore = std::min(bestScore, minimax(depth-1,alpha, beta, board,!whiteTeam));

            board[move[1]][move[0]] = board[move[3]][move[2]];
            board[move[3]][move[2]] = temp;

            beta = std::min(beta, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    }

}

QVector<int> AlphaBeta::minimaxRoot(int depth, int **board, bool whiteTeam) {
    QVector<QVector<int>> allMoves = getAllMoves(board,whiteTeam);
    int bestScore;
    QVector<int> bestMove;


    if(whiteTeam){
        bestScore = INT_MIN;
    }else{
        bestScore = INT_MAX;
    }

    for(QVector<int> move: allMoves){
        int temp = board[move[3]][move[2]];
        board[move[3]][move[2]] = board[move[1]][move[0]];
        board[move[1]][move[0]] = 0;

        int score = minimax(depth, INT_MIN, INT_MAX, board, whiteTeam);

        board[move[1]][move[0]] = board[move[3]][move[2]];
        board[move[3]][move[2]] = temp;

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