#include "alphaBeta.h"
#include "Board/board.h"

AlphaBeta::AlphaBeta(Controller* controller, int searchDepth) {
    this->controller = controller;
    this->mt = std::mt19937(rd());
    this->searchDepth = searchDepth;
}

Move AlphaBeta::findMove(bool whiteTeam) {

    Move move = minimaxRoot(this->searchDepth, whiteTeam);

    return move;
}

char AlphaBeta::findUpgrade(Move move) {

    return 'q';

    //TODO maybe change after neural network, too slow without it.
    /**int bestChoice = promotionRoot(move, 1);

    if(bestChoice < 0){
        bestChoice *= -1;
    }

    char choice = 0;

    if(bestChoice == 3){
        choice = 'k';
    }else if(bestChoice == 5){
        choice = 'q';
    }

    return choice;**/
}

int AlphaBeta::promotionRoot(Move move, int depth){
    int bestScore;
    int bestChoice = 0;
    int choices[] = {3, 5}; //possible upgrades: knight, queen

    bool whiteTeam = controller->getBoard()->getPiece(move.init.x(), move.init.y()) > 0;

    if( whiteTeam ){
        bestScore = INT_MIN;
    }else{
        bestScore = INT_MAX;
    }

    int tempEndPiece = controller->getBoard()->getPiece(move.end.x(), move.end.y());
    int tempStartPiece = controller->getBoard()->getPiece(move.init.x(), move.init.y());

    controller->getBoard()->setPiece(move.init.x(), move.init.y(), 0);

    for (int upgradePiece : choices) {
        if(!whiteTeam){
            upgradePiece *= -1;
        }

        controller->getBoard()->setPiece(move.end.x(), move.end.y(), upgradePiece);

        int score = minimax(depth, INT_MIN, INT_MAX,  !whiteTeam);

        if(whiteTeam){
            if(score > bestScore){
                bestScore = score;
                bestChoice = upgradePiece;
            }
        }else{
            if(score < bestScore){
                bestScore = score;
                bestChoice = upgradePiece;
            }
        }
    }

    controller->getBoard()->setPiece(move.init.x(), move.init.y(), tempStartPiece);
    controller->getBoard()->setPiece(move.end.x(), move.end.y(), tempEndPiece);


    return bestChoice;
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
    std::uniform_int_distribution<int> evalRandomness(-6,6);

    int score = 0;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            score += map.getItem(board[y][x]);
        }
    }

    score += evalRandomness(mt);
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
            ElPassant whitePassant, blackPassant;

            doMove(move, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);

            bestScore = std::max(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            undoMove(move, temp, rook, king, undoType, whitePassant, blackPassant);

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
            ElPassant whitePassant, blackPassant;

            doMove(move, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);

            bestScore = std::min(bestScore, minimax(depth-1,alpha, beta, !whiteTeam));

            undoMove(move, temp, rook, king, undoType, whitePassant, blackPassant);

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
        int temp, king, rook, undoType;
        ElPassant whitePassant, blackPassant;


        doMove(move, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);

        int score = minimax(depth, INT_MIN, INT_MAX,  !whiteTeam);

        undoMove(move, temp, rook, king, undoType, whitePassant, blackPassant);

        if(whiteTeam){
            if(score >= bestScore){
                bestScore = score;
                bestMove = move;
            }
        }else{
            if(score <= bestScore){
                bestScore = score;
                bestMove = move;
            }
        }
    }

    return bestMove;
}

void AlphaBeta::doMove(Move move, int* temp, int* rook, int* king, int* undoType, ElPassant* whitePassant, ElPassant* blackPassant) {
    if(move.special==0){// normal move

        if(move.init.y()==7 && move.init.x()==0 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==2){
            if(!controller->getBoard()->getWLR()){
                *undoType = 1;
                controller->getBoard()->setWLR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==7 && move.init.x()==7 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==2){
            if(!controller->getBoard()->getWRR()){
                *undoType = 2;
                controller->getBoard()->setWRR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==0 && move.init.x()==0 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==-2){
            if(!controller->getBoard()->getBLR()){
                *undoType = 3;
                controller->getBoard()->setBLR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==0 && move.init.x()==7 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==-2){
            if(!controller->getBoard()->getBRR()){
                *undoType = 4;
                controller->getBoard()->setBRR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==7 && move.init.x()==4 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==6){
            if(!controller->getBoard()->getWKing()){
                *undoType = 5;
                controller->getBoard()->setWKing(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==0 && move.init.x()==4 && controller->getBoard()->getPiece(move.init.x(),move.init.y())==-6){
            if(!controller->getBoard()->getBKing()){
                *undoType = 6;
                controller->getBoard()->setBKing(true);
            }else{
                *undoType = 0;
            }
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
    }else if(move.special==4){ //pawn promotion
        *temp = controller->getBoard()->getPiece(move.end.x(),move.end.y());

        char choice = findUpgrade(move);

        int piece = 0;

        if(choice == 'r'){
            if(controller->getBoard()->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 2;
            }else {
                piece = -2;
            }
        }else if(choice == 'k'){
            if(controller->getBoard()->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 3;
            }else {
                piece = -3;
            }
        }else if(choice == 'b'){
            if(controller->getBoard()->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 4;
            }else {
                piece = -4;
            }
        }else if(choice == 'q'){
            if(controller->getBoard()->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 5;
            }else {
                piece = -5;
            }
        }

        controller->getBoard()->setPiece(move.init.x(), move.init.y(), 0);
        controller->getBoard()->setPiece(move.end.x(), move.end.y(), piece);
    }

    *whitePassant = controller->getBoard()->getWhitePassant();
    *blackPassant = controller->getBoard()->getBlackPassant();

    controller->getBoard()->clearPassant(true);
    controller->getBoard()->clearPassant(false);
}

void AlphaBeta::undoMove(Move move, int temp, int rook, int king, int undoType, ElPassant whitePassant, ElPassant blackPassant) {
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
    }else if(move.special == 4){
        if(controller->getBoard()->getPiece(move.end.x(), move.end.y()) > 0){
            controller->getBoard()->setPiece(move.init.x(),move.init.y(), 1);
        }else{
            controller->getBoard()->setPiece(move.init.x(),move.init.y(), -1);
        }

        controller->getBoard()->setPiece(move.end.x(),move.end.y(), temp);
    }

    controller->getBoard()->setPassant(true,whitePassant);
    controller->getBoard()->setPassant(false,blackPassant);
}
