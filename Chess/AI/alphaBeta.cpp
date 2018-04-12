#include "alphaBeta.h"
#include "Board/board.h"

AlphaBeta::AlphaBeta(Controller* controller) {
    this->controller = controller;

}

Move AlphaBeta::findMove(bool whiteTeam) {

    Move move = minimaxRoot(4, whiteTeam);

    return move;
}

char AlphaBeta::findUpgrade() {
    return randomMove.getRandomUpgrade();
}

QVector<Move> AlphaBeta::getAllMoves(bool whiteTeam) {
    QVector<Move> allPossibleMoves;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(controller->getBoard()->getPiece(x,y) < 0 && !whiteTeam){
                QVector<Move> moves = controller->getMoves(x,y);

                allPossibleMoves.append(moves);
            }else if(controller->getBoard()->getPiece(x,y) > 0 && whiteTeam){
                QVector<Move> moves = controller->getMoves(x,y);

                allPossibleMoves.append(moves);
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

    QVector<Move> allMoves = getAllMoves(whiteTeam);

    if(whiteTeam){
        int bestScore = INT_MIN;

        for(Move move: allMoves){

            int temp, king, rook;

            if(move.special==0){// normal move
                temp = controller->getBoard()->getPiece(move.end.x(),move.end.y());
                controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
            }else if(move.special==1){//passant move
                temp = controller->getBoard()->getPiece(move.end.x(),move.init.y());
                controller->getBoard()->setPiece(move.end.x(),move.init.y(),0);
                controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
            }else if(move.special==2){// castling left
                rook = controller->getBoard()->getPiece(0,move.init.y());
                king = controller->getBoard()->getPiece(4,move.init.y());

                controller->getBoard()->setPiece(0,move.init.y(),0);
                controller->getBoard()->setPiece(4,move.init.y(),0);
                controller->getBoard()->setPiece(2,move.init.y(),king);
                controller->getBoard()->setPiece(3,move.init.y(),rook);

                if(move.init.y()==0){
                    controller->getBoard()->setBLR(true);
                    controller->getBoard()->setBKing(true);
                }else{
                    controller->getBoard()->setWLR(true);
                    controller->getBoard()->setWKing(true);
                }
            }else if(move.special==3){//castling right
                rook = controller->getBoard()->getPiece(7,move.init.y());
                king = controller->getBoard()->getPiece(4,move.init.y());

                controller->getBoard()->setPiece(7,move.init.y(),0);
                controller->getBoard()->setPiece(4,move.init.y(),0);
                controller->getBoard()->setPiece(6,move.init.y(),king);
                controller->getBoard()->setPiece(5,move.init.y(),rook);

                if(move.init.y()==0){
                    controller->getBoard()->setBRR(true);
                    controller->getBoard()->setBKing(true);
                }else{
                    controller->getBoard()->setWRR(true);
                    controller->getBoard()->setWKing(true);
                }
            }

            bestScore = std::max(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            if(move.special==0){// normal move
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),controller->getBoard()->getPiece(move.end.x(),move.end.y()));
                controller->getBoard()->setPiece(move.end.x(),move.end.y(), temp);
            }else if(move.special==1){//passant move
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),controller->getBoard()->getPiece(move.end.x(),move.end.y()));
                controller->getBoard()->setPiece(move.end.x(),move.end.y(),0);
                controller->getBoard()->setPiece(move.end.x(),move.init.y(),temp);
            }else if(move.special==2){// castling left
                controller->getBoard()->setPiece(2,move.init.y(),0);
                controller->getBoard()->setPiece(3,move.init.y(),0);
                controller->getBoard()->setPiece(0,move.init.y(),rook);
                controller->getBoard()->setPiece(4,move.init.y(),king);
            }else if(move.special==3){//castling right
                controller->getBoard()->setPiece(6,move.init.y(),0);
                controller->getBoard()->setPiece(5,move.init.y(),0);
                controller->getBoard()->setPiece(0,move.init.y(),rook);
                controller->getBoard()->setPiece(4,move.init.y(),king);

                if(move.init.y()==0){
                    controller->getBoard()->setBRR(false);
                    controller->getBoard()->setBKing(false);
                }else{
                    controller->getBoard()->setWRR(false);
                    controller->getBoard()->setWKing(false);
                }
            }

            alpha = std::max(alpha, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    } else{
        int bestScore = INT_MAX;

        for(Move move: allMoves){
            int temp, king, rook;

            if(move.special==0){// normal move
                temp = controller->getBoard()->getPiece(move.end.x(),move.end.y());
                controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
            }else if(move.special==1){//passant move
                temp = controller->getBoard()->getPiece(move.end.x(),move.init.y());
                controller->getBoard()->setPiece(move.end.x(),move.init.y(),0);
                controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
            }else if(move.special==2){// castling left
                rook = controller->getBoard()->getPiece(0,move.init.y());
                king = controller->getBoard()->getPiece(4,move.init.y());

                controller->getBoard()->setPiece(0,move.init.y(),0);
                controller->getBoard()->setPiece(4,move.init.y(),0);
                controller->getBoard()->setPiece(2,move.init.y(),king);
                controller->getBoard()->setPiece(3,move.init.y(),rook);

                if(move.init.y()==0){
                    controller->getBoard()->setBLR(true);
                    controller->getBoard()->setBKing(true);
                }else{
                    controller->getBoard()->setWLR(true);
                    controller->getBoard()->setWKing(true);
                }
            }else if(move.special==3){//castling right
                rook = controller->getBoard()->getPiece(7,move.init.y());
                king = controller->getBoard()->getPiece(4,move.init.y());

                controller->getBoard()->setPiece(7,move.init.y(),0);
                controller->getBoard()->setPiece(4,move.init.y(),0);
                controller->getBoard()->setPiece(6,move.init.y(),king);
                controller->getBoard()->setPiece(5,move.init.y(),rook);

                if(move.init.y()==0){
                    controller->getBoard()->setBRR(true);
                    controller->getBoard()->setBKing(true);
                }else{
                    controller->getBoard()->setWRR(true);
                    controller->getBoard()->setWKing(true);
                }
            }

            bestScore = std::min(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            if(move.special==0){// normal move
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),controller->getBoard()->getPiece(move.end.x(),move.end.y()));
                controller->getBoard()->setPiece(move.end.x(),move.end.y(), temp);
            }else if(move.special==1){//passant move
                controller->getBoard()->setPiece(move.init.x(),move.init.y(),controller->getBoard()->getPiece(move.end.x(),move.end.y()));
                controller->getBoard()->setPiece(move.end.x(),move.end.y(),0);
                controller->getBoard()->setPiece(move.end.x(),move.init.y(),temp);
            }else if(move.special==2){// castling left
                controller->getBoard()->setPiece(2,move.init.y(),0);
                controller->getBoard()->setPiece(3,move.init.y(),0);
                controller->getBoard()->setPiece(0,move.init.y(),rook);
                controller->getBoard()->setPiece(4,move.init.y(),king);
            }else if(move.special==3){//castling right
                controller->getBoard()->setPiece(6,move.init.y(),0);
                controller->getBoard()->setPiece(5,move.init.y(),0);
                controller->getBoard()->setPiece(0,move.init.y(),rook);
                controller->getBoard()->setPiece(4,move.init.y(),king);

                if(move.init.y()==0){
                    controller->getBoard()->setBRR(false);
                    controller->getBoard()->setBKing(false);
                }else{
                    controller->getBoard()->setWRR(false);
                    controller->getBoard()->setWKing(false);
                }
            }

            beta = std::min(beta, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    }

}

Move AlphaBeta::minimaxRoot(int depth, bool whiteTeam) {
    QVector<Move> allMoves = getAllMoves(whiteTeam);
    int bestScore;
    Move bestMove(QPoint(-1,-1),QPoint(-1,-1));


    if(whiteTeam){
        bestScore = INT_MIN;
    }else{
        bestScore = INT_MAX;
    }

    for(Move move: allMoves){
        int temp, king, rook;

        if(move.special==0){// normal move
            temp = controller->getBoard()->getPiece(move.end.x(),move.end.y());
            controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
            controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
        }else if(move.special==1){//passant move
            temp = controller->getBoard()->getPiece(move.end.x(),move.init.y());
            controller->getBoard()->setPiece(move.end.x(),move.init.y(),0);
            controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
            controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
        }else if(move.special==2){// castling left
            rook = controller->getBoard()->getPiece(0,move.init.y());
            king = controller->getBoard()->getPiece(4,move.init.y());

            controller->getBoard()->setPiece(0,move.init.y(),0);
            controller->getBoard()->setPiece(4,move.init.y(),0);
            controller->getBoard()->setPiece(2,move.init.y(),king);
            controller->getBoard()->setPiece(3,move.init.y(),rook);

            if(move.init.y()==0){
                controller->getBoard()->setBLR(true);
                controller->getBoard()->setBKing(true);
            }else{
                controller->getBoard()->setWLR(true);
                controller->getBoard()->setWKing(true);
            }
        }else if(move.special==3){//castling right
            rook = controller->getBoard()->getPiece(7,move.init.y());
            king = controller->getBoard()->getPiece(4,move.init.y());

            controller->getBoard()->setPiece(7,move.init.y(),0);
            controller->getBoard()->setPiece(4,move.init.y(),0);
            controller->getBoard()->setPiece(6,move.init.y(),king);
            controller->getBoard()->setPiece(5,move.init.y(),rook);

            if(move.init.y()==0){
                controller->getBoard()->setBRR(true);
                controller->getBoard()->setBKing(true);
            }else{
                controller->getBoard()->setWRR(true);
                controller->getBoard()->setWKing(true);
            }
        }

        int score = minimax(depth, INT_MIN, INT_MAX,  whiteTeam);

        if(move.special==0){// normal move
            controller->getBoard()->setPiece(move.init.x(),move.init.y(),controller->getBoard()->getPiece(move.end.x(),move.end.y()));
            controller->getBoard()->setPiece(move.end.x(),move.end.y(), temp);
        }else if(move.special==1){//passant move
            controller->getBoard()->setPiece(move.init.x(),move.init.y(),controller->getBoard()->getPiece(move.end.x(),move.end.y()));
            controller->getBoard()->setPiece(move.end.x(),move.end.y(),0);
            controller->getBoard()->setPiece(move.end.x(),move.init.y(),temp);
        }else if(move.special==2){// castling left
            controller->getBoard()->setPiece(2,move.init.y(),0);
            controller->getBoard()->setPiece(3,move.init.y(),0);
            controller->getBoard()->setPiece(0,move.init.y(),rook);
            controller->getBoard()->setPiece(4,move.init.y(),king);
        }else if(move.special==3){//castling right
            controller->getBoard()->setPiece(6,move.init.y(),0);
            controller->getBoard()->setPiece(5,move.init.y(),0);
            controller->getBoard()->setPiece(0,move.init.y(),rook);
            controller->getBoard()->setPiece(4,move.init.y(),king);

            if(move.init.y()==0){
                controller->getBoard()->setBRR(false);
                controller->getBoard()->setBKing(false);
            }else{
                controller->getBoard()->setWRR(false);
                controller->getBoard()->setWKing(false);
            }
        }

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