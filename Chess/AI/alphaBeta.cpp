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

int AlphaBeta::evaluateBoard(std::array<std::array<int,8>,8> board) {

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

            int temp, king, rook, undoType;

            doMove(move, &temp, &rook, &king, &undoType);

            controller->getBoard()->printBoard();
            std::cout << "-------------------------" << std::endl;
            std::cout << "Move: " << move.init.x() << "," << move.init.y() << " to " << move.end.x() << "," << move.end.y() << ". Type: " << move.special << std::endl;
            std::cout << std::endl;

            bestScore = std::max(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            undoMove(move, temp, rook, king, undoType);

            alpha = std::max(alpha, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    } else{
        int bestScore = INT_MAX;

        for(Move move: allMoves){
            int temp, king, rook, undoType;

            doMove(move, &temp, &rook, &king, &undoType);

            controller->getBoard()->printBoard();
            std::cout << "-------------------------" << std::endl;
            std::cout << "Move: " << move.init.x() << "," << move.init.y() << " to " << move.end.x() << "," << move.end.y() << ". Type: " << move.special << std::endl;
            std::cout << std::endl;

            bestScore = std::min(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            undoMove(move, temp, rook, king, undoType);

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

    std::cout << "Starting board:" << std::endl;
    controller->getBoard()->printBoard();
    std::cout << std::endl;

    if(whiteTeam){
        bestScore = INT_MIN;
    }else{
        bestScore = INT_MAX;
    }

    for(Move move: allMoves){
        int temp, king, rook, undoType;

        doMove(move, &temp, &rook, &king, &undoType);

        controller->getBoard()->printBoard();
        std::cout << "-------------------------" << std::endl;
        std::cout << "Root Move: " << move.init.x() << "," << move.init.y() << " to " << move.end.x() << "," << move.end.y() << ". Type: " << move.special << std::endl;
        std::cout << std::endl;

        int score = minimax(depth, INT_MIN, INT_MAX,  !whiteTeam);

        undoMove(move, temp, rook, king, undoType);

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

void AlphaBeta::doMove(Move move, int* temp, int* rook, int* king, int* undoType) {
    if(move.special==0){// normal move

        if(move.init.y()==7 && move.init.x()==0 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==2){
            controller->getBoard()->setWLR(true);
            *undoType = 1;
        }
        else if(move.init.y()==7 && move.init.x()==7 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==2){
            controller->getBoard()->setWRR(true);
            *undoType = 2;
        }
        else if(move.init.y()==0 && move.init.x()==0 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==-2){
            controller->getBoard()->setBLR(true);
            *undoType = 3;
        }
        else if(move.init.y()==0 && move.init.x()==7 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==-2){
            controller->getBoard()->setBRR(true);
            *undoType = 4;
        }
        else if(move.init.y()==7 && move.init.x()==4 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==6){
            controller->getBoard()->setWKing(true);
            *undoType = 5;
        }
        else if(move.init.y()==0 && move.init.x()==4 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==-6){
            controller->getBoard()->setBKing(true);
            *undoType = 6;
        }else{
            *undoType = 0;
        }

        *temp = controller->getBoard()->getPiece(move.end.x(),move.end.y());
        controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
        controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
    }else if(move.special==1){//passant move
        *temp = controller->getBoard()->getPiece(move.end.x(),move.init.y());
        controller->getBoard()->setPiece(move.end.x(),move.init.y(),0);
        controller->getBoard()->setPiece(move.end.x(),move.end.y(), controller->getBoard()->getPiece(move.init.x(),move.init.y()));
        controller->getBoard()->setPiece(move.init.x(),move.init.y(),0);
    }else if(move.special==2){// castling left
        *rook = controller->getBoard()->getPiece(0,move.init.y());
        *king = controller->getBoard()->getPiece(4,move.init.y());

        controller->getBoard()->setPiece(0,move.init.y(),0);
        controller->getBoard()->setPiece(4,move.init.y(),0);
        controller->getBoard()->setPiece(2,move.init.y(),*king);
        controller->getBoard()->setPiece(3,move.init.y(),*rook);

        if(move.init.y()==0){
            controller->getBoard()->setBLR(true);
            controller->getBoard()->setBKing(true);
        }else{
            controller->getBoard()->setWLR(true);
            controller->getBoard()->setWKing(true);
        }
    }else if(move.special==3){//castling right
        *rook = controller->getBoard()->getPiece(7,move.init.y());
        *king = controller->getBoard()->getPiece(4,move.init.y());

        controller->getBoard()->setPiece(7,move.init.y(),0);
        controller->getBoard()->setPiece(4,move.init.y(),0);
        controller->getBoard()->setPiece(6,move.init.y(),*king);
        controller->getBoard()->setPiece(5,move.init.y(),*rook);

        if(move.init.y()==0){
            controller->getBoard()->setBRR(true);
            controller->getBoard()->setBKing(true);
        }else{
            controller->getBoard()->setWRR(true);
            controller->getBoard()->setWKing(true);
        }
    }
}

void AlphaBeta::undoMove(Move move, int temp, int rook, int king, int undoType) {
    if(move.special==0){// normal move

        switch (undoType){
            case 1:
                controller->getBoard()->setWLR(false);
                break;
            case 2:
                controller->getBoard()->setWRR(false);
                break;
            case 3:
                controller->getBoard()->setBLR(false);
                break;
            case 4:
                controller->getBoard()->setBRR(false);
                break;
            case 5:
                controller->getBoard()->setWKing(false);
                break;
            case 6:
                controller->getBoard()->setBKing(false);
                break;
            default:
                break;
        }

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

        if(move.init.y()==0){
            controller->getBoard()->setBLR(false);
            controller->getBoard()->setBKing(false);
        }else{
            controller->getBoard()->setWLR(false);
            controller->getBoard()->setWKing(false);
        }
    }else if(move.special==3){//castling right
        controller->getBoard()->setPiece(6,move.init.y(),0);
        controller->getBoard()->setPiece(5,move.init.y(),0);
        controller->getBoard()->setPiece(7,move.init.y(),rook);
        controller->getBoard()->setPiece(4,move.init.y(),king);

        if(move.init.y()==0){
            controller->getBoard()->setBRR(false);
            controller->getBoard()->setBKing(false);
        }else{
            controller->getBoard()->setWRR(false);
            controller->getBoard()->setWKing(false);
        }
    }
}
