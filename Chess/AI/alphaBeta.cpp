#include "alphaBeta.h"


/**
 *  Creates an instance of Alpha Beta for determining chess moves with a specified search depth
 * 
 * @param controller game controller
 * @param searchDepth depth of alpha beta to search for
 */
AlphaBeta::AlphaBeta(Controller* controller, int searchDepth, std::string graphPath, std::string checkpointPath) {
    this->controller = controller;
    this->mt = std::mt19937(rd());
    this->searchDepth = searchDepth;
    this->nn = new NeuralNetwork(graphPath, checkpointPath);
}

/**
 *  Uses Alpha Beta pruning to determine the "best" move to make.
 * 
 * @param whiteTeam whether or not we're searching for a white move or black move
 * @return "best" move to make
 */
Move AlphaBeta::findMove(bool whiteTeam, int moveNumber) {

    if(!whiteTeam && moveNumber == 1){
        QPoint strt;
        strt.setX(4);
        strt.setY(1);

        QPoint end;
        end.setX(4);
        end.setY(3);

        return {strt,end,0};
    }else if(!whiteTeam && moveNumber == 2){
        QPoint strt;
        strt.setX(1);
        strt.setY(0);

        QPoint end;
        end.setX(2);
        end.setY(2);

        return {strt,end,0};
    }else if(!whiteTeam && moveNumber == 3){
        QPoint strt;
        strt.setX(5);
        strt.setY(0);

        QPoint end;
        end.setX(2);
        end.setY(3);

        return {strt,end,0};
    }

    int ply;

    if(moveNumber < 5 && this->searchDepth - 4 > 0){
        ply = this->searchDepth - 4;
    }else if(moveNumber < 10 && this->searchDepth - 2 > 0){
        ply = this->searchDepth - 2;
    }else{
        ply = this->searchDepth;
    }

    Move move = minimaxRoot(ply, whiteTeam);

    return move;
}

/**
 * Chooses which piece to upgrade the pawn to
 * 
 * @param move the move that is being upgraded
 * @return choice of "best" upgrade
 */
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

/**
 * Minimax Root for finding a pawn promotion
 * 
 * @param move Move that is being promoted
 * @param depth Depth to search
 * @return best choice to upgrade, either a knight or a queen
 */
int AlphaBeta::promotionRoot(Move move, int depth){
    /*int bestScore;
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
    */
    return -1;
}

/**
 *  Gets all the possible moves for a specified team
 * 
 * @param whiteTeam whether we're searching for white moves or black moves
 * @return Vector of all possible moves
 */
QVector<Move> AlphaBeta::getAllMoves(Board* board, bool whiteTeam) {
    QVector<Move> allPossibleMoves;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(board->getPiece(x,y) < 0 && !whiteTeam){
                QVector<Move> moves = controller->getMoves(board, x,y);

                allPossibleMoves.append(moves);
            }else if(board->getPiece(x,y) > 0 && whiteTeam){
                QVector<Move> moves = controller->getMoves(board, x,y);

                allPossibleMoves.append(moves);
            }
        }
    }

    return allPossibleMoves;
}

/**
 *  Evaluates the score of the current board
 * 
 * @param board 2D array representing the current board state
 * @return score of the board
 */
int AlphaBeta::evaluateBoard(std::array<std::array<int,8>,8> board) {
    std::uniform_int_distribution<int> evalRandomness(-6,6);

    int score = 0;
    /*for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            score += map.getItem(board[y][x]);
        }
    }*/

    int res[2];
    this->nn->calculateScore(board, res);

    score += res[0];
    score += res[1];

    score += evalRandomness(mt);
    return score;

}

/**
 *  Performs an alpha beta minimax
 * 
 * @param depth Depth to Search
 * @param alpha Alpha Value
 * @param beta Beta Value
 * @param whiteTeam Whether it's white teams turn or black teams
 * @return Score
 */
int AlphaBeta::minimax(Board* board, int depth,int alpha, int beta, bool whiteTeam) {
    if(depth == 0){
        return evaluateBoard(board->getBoard());
    }

    QVector<Move> allMoves = getAllMoves(board, whiteTeam);

    if(whiteTeam){
        int bestScore = INT_MIN;

        for(Move move: allMoves){

            int temp, king, rook, undoType;
            ElPassant whitePassant, blackPassant;

            doMove(move, board, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);

            bestScore = std::max(bestScore, minimax(board, depth-1,alpha, beta, !whiteTeam));

            undoMove(move, board, temp, rook, king, undoType, whitePassant, blackPassant);

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

            doMove(move, board, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);

            bestScore = std::min(bestScore, minimax(board, depth-1,alpha, beta, !whiteTeam));

            undoMove(move, board, temp, rook, king, undoType, whitePassant, blackPassant);

            beta = std::min(beta, bestScore);
            if(beta <= alpha){
                return bestScore;
            }
        }
        return bestScore;
    }

}

std::pair<int, int> AlphaBeta::minimaxRootSection(Board* board, int depth, bool whiteTeam, QVector<Move> moves, int start, int end) {
    int bestScore;
    int bestLoc = -1;
    if(whiteTeam){
        bestScore = INT_MIN;
    }else{
        bestScore = INT_MAX;
    }

    for(int i = 0; start+i < end; i++){
        int temp, king, rook, undoType;
        ElPassant whitePassant, blackPassant;


        doMove(moves[start+i], board, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);

        int score = minimax(board, depth, INT_MIN, INT_MAX,  !whiteTeam);

        undoMove(moves[start+i], board, temp, rook, king, undoType, whitePassant, blackPassant);

        if(whiteTeam){
            if(score >= bestScore){
                bestScore = score;
                bestLoc = start+i;
            }
        }else{
            if(score <= bestScore){
                bestScore = score;
                bestLoc = start+i;
            }
        }
    }

    return std::make_pair(bestScore,bestLoc);
}

/**
 *  Minimax Root for finding the "best" move
 * 
 * @param depth Depth to search
 * @param whiteTeam Whether white team or not
 * @return Best Move
 */
Move AlphaBeta::minimaxRoot(int depth, bool whiteTeam) {
    QVector<Move> allMoves = getAllMoves(this->controller->getBoard(), whiteTeam);
    int bestScore;
    Move bestMove(QPoint(-1,-1),QPoint(-1,-1));

        if(whiteTeam){
            bestScore = INT_MIN;
        }else{
            bestScore = INT_MAX;
        }

    int nThreads = 4;

    int k = allMoves.size() / nThreads;
    int m = allMoves.size() % nThreads;

    std::vector<std::future<std::pair<int,int>>> futureScores;
    Board* boardCopies[nThreads];

    for(int i = 0; i < nThreads; i++){
        boardCopies[i] = this->controller->getBoard()->createCopy();
    }

    for(int i = 0; i < nThreads; i++){
        futureScores.push_back(std::async(std::launch::async, &AlphaBeta::minimaxRootSection, this, boardCopies[i], depth, whiteTeam,
                allMoves, i*k + std::min(i , m), (i+1)*k + std::min((i+1), m)));
    }

    for (int i = 0; i < nThreads; ++i) {
        futureScores[i].wait();
    }

    for(int i = 0; i < nThreads; i++){
        auto result = futureScores[i].get();

        if(whiteTeam){
            if(result.first >= bestScore){
                bestScore = result.first;
                bestMove = allMoves[result.second];
            }
        }else{
            if(result.first <= bestScore){
                bestScore = result.first;
                bestMove = allMoves[result.second];;
            }
        }
    }

//    if(whiteTeam){
//        bestScore = INT_MIN;
//    }else{
//        bestScore = INT_MAX;
//    }

//    for(Move move: allMoves){
//        int temp, king, rook, undoType;
//        ElPassant whitePassant, blackPassant;
//
//
//        doMove(move, &temp, &rook, &king, &undoType, &whitePassant, &blackPassant);
//
//        int score = minimax(depth, INT_MIN, INT_MAX,  !whiteTeam);
//
//        undoMove(move, temp, rook, king, undoType, whitePassant, blackPassant);
//
//        if(whiteTeam){
//            if(score >= bestScore){
//                bestScore = score;
//                bestMove = move;
//            }
//        }else{
//            if(score <= bestScore){
//                bestScore = score;
//                bestMove = move;
//            }
//        }
//    }

    return bestMove;
}

/**
 *  Simulates given move on the game board
 * 
 * @param move Move to make
 * @param temp pointer to store what is being moved ontop of
 * @param rook 
 * @param king
 * @param undoType What type of move we have to undo
 * @param whitePassant 
 * @param blackPassant
 */
void AlphaBeta::doMove(Move move, Board* board, int* temp, int* rook, int* king, int* undoType, ElPassant* whitePassant, ElPassant* blackPassant) {
    if(move.special==0){// normal move

        if(move.init.y()==7 && move.init.x()==0 && board->getPiece(move.init.x(),move.init.y())==2){
            if(!board->getWLR()){
                *undoType = 1;
                board->setWLR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==7 && move.init.x()==7 && board->getPiece(move.init.x(),move.init.y())==2){
            if(!board->getWRR()){
                *undoType = 2;
                board->setWRR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==0 && move.init.x()==0 && board->getPiece(move.init.x(),move.init.y())==-2){
            if(!board->getBLR()){
                *undoType = 3;
                board->setBLR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==0 && move.init.x()==7 && board->getPiece(move.init.x(),move.init.y())==-2){
            if(!board->getBRR()){
                *undoType = 4;
                board->setBRR(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==7 && move.init.x()==4 && board->getPiece(move.init.x(),move.init.y())==6){
            if(!board->getWKing()){
                *undoType = 5;
                board->setWKing(true);
            }else{
                *undoType = 0;
            }
        }
        else if(move.init.y()==0 && move.init.x()==4 && board->getPiece(move.init.x(),move.init.y())==-6){
            if(!board->getBKing()){
                *undoType = 6;
                board->setBKing(true);
            }else{
                *undoType = 0;
            }
        }else{
            *undoType = 0;
        }

        *temp = board->getPiece(move.end.x(),move.end.y());
        board->setPiece(move.end.x(),move.end.y(), board->getPiece(move.init.x(),move.init.y()));
        board->setPiece(move.init.x(),move.init.y(),0);
    }else if(move.special==1){//passant move

        *temp = board->getPiece(move.end.x(),move.init.y());
        board->setPiece(move.end.x(),move.init.y(),0);
        board->setPiece(move.end.x(),move.end.y(), board->getPiece(move.init.x(),move.init.y()));
        board->setPiece(move.init.x(),move.init.y(),0);

    }else if(move.special==2){// castling left
        *rook = board->getPiece(0,move.init.y());
        *king = board->getPiece(4,move.init.y());

        board->setPiece(0,move.init.y(),0);
        board->setPiece(4,move.init.y(),0);
        board->setPiece(2,move.init.y(),*king);
        board->setPiece(3,move.init.y(),*rook);

        if(move.init.y()==0){
            board->setBLR(true);
            board->setBKing(true);
        }else{
            board->setWLR(true);
            board->setWKing(true);
        }
    }else if(move.special==3){//castling right
        *rook = board->getPiece(7,move.init.y());
        *king = board->getPiece(4,move.init.y());

        board->setPiece(7,move.init.y(),0);
        board->setPiece(4,move.init.y(),0);
        board->setPiece(6,move.init.y(),*king);
        board->setPiece(5,move.init.y(),*rook);

        if(move.init.y()==0){
            board->setBRR(true);
            board->setBKing(true);
        }else{
            board->setWRR(true);
            board->setWKing(true);
        }
    }else if(move.special==4){ //pawn promotion
        *temp = board->getPiece(move.end.x(),move.end.y());

        char choice = findUpgrade(move);

        int piece = 0;

        if(choice == 'r'){
            if(board->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 2;
            }else {
                piece = -2;
            }
        }else if(choice == 'k'){
            if(board->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 3;
            }else {
                piece = -3;
            }
        }else if(choice == 'b'){
            if(board->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 4;
            }else {
                piece = -4;
            }
        }else if(choice == 'q'){
            if(board->getPiece(move.init.x(), move.init.y()) > 0){
                piece = 5;
            }else {
                piece = -5;
            }
        }

        board->setPiece(move.init.x(), move.init.y(), 0);
        board->setPiece(move.end.x(), move.end.y(), piece);
    }

    *whitePassant = board->getWhitePassant();
    *blackPassant = board->getBlackPassant();

    board->clearPassant(true);
    board->clearPassant(false);
}

/**
 *  Undoes a specified move on the game board
 * 
 * @param move Move to undo
 * @param temp piece that was covered
 * @param rook 
 * @param king
 * @param undoType Type of move to undo
 * @param whitePassant
 * @param blackPassant
 */
void AlphaBeta::undoMove(Move move, Board* board, int temp, int rook, int king, int undoType, ElPassant whitePassant, ElPassant blackPassant) {
    if(move.special==0){// normal move

        switch (undoType){
            case 1:
                board->setWLR(false);
                break;
            case 2:
                board->setWRR(false);
                break;
            case 3:
                board->setBLR(false);
                break;
            case 4:
                board->setBRR(false);
                break;
            case 5:
                board->setWKing(false);
                break;
            case 6:
                board->setBKing(false);
                break;
            default:
                break;
        }

        board->setPiece(move.init.x(),move.init.y(),board->getPiece(move.end.x(),move.end.y()));
        board->setPiece(move.end.x(),move.end.y(), temp);
    }else if(move.special==1){//passant move
        board->setPiece(move.init.x(),move.init.y(),board->getPiece(move.end.x(),move.end.y()));
        board->setPiece(move.end.x(),move.end.y(),0);
        board->setPiece(move.end.x(),move.init.y(),temp);
    }else if(move.special==2){// castling left
        board->setPiece(2,move.init.y(),0);
        board->setPiece(3,move.init.y(),0);
        board->setPiece(0,move.init.y(),rook);
        board->setPiece(4,move.init.y(),king);

        if(move.init.y()==0){
            board->setBLR(false);
            board->setBKing(false);
        }else{
            board->setWLR(false);
            board->setWKing(false);
        }
    }else if(move.special==3){//castling right
        board->setPiece(6,move.init.y(),0);
        board->setPiece(5,move.init.y(),0);
        board->setPiece(7,move.init.y(),rook);
        board->setPiece(4,move.init.y(),king);

        if(move.init.y()==0){
            board->setBRR(false);
            board->setBKing(false);
        }else{
            board->setWRR(false);
            board->setWKing(false);
        }
    }else if(move.special == 4){
        if(board->getPiece(move.end.x(), move.end.y()) > 0){
            board->setPiece(move.init.x(),move.init.y(), 1);
        }else{
            board->setPiece(move.init.x(),move.init.y(), -1);
        }

        board->setPiece(move.end.x(),move.end.y(), temp);
    }

    board->setPassant(true,whitePassant);
    board->setPassant(false,blackPassant);
}
