#include "board.h"

/**
 *  -6 = BLK KING
 *  -5 = BLK QUEEN
 *  -4 = BLK BISHOP
 *  -3 = BLK KNIGHT
 *  -2 = BLK ROOK
 *  -1 = BLK PAWN
 *
 *   0 = NO PIECE
 *
 *   1 = WHT PAWN
 *   2 = WHT ROOK
 *   3 = WHT KNIGHT
 *   4 = WHT BISHOP
 *   5 = WHT QUEEN
 *   6 = WHT KING
 */

Board::Board() {
    board = new int*[8];
    for (int i = 0; i < 8; ++i) {
        board[i] = new int[8];
    }

    initBoard();
    windowSet = false;
}

void Board::initBoard(){

    QMessageBox msg;
    msg.setText("Choose a game mode");
    QPushButton *op = msg.addButton("One Player", QMessageBox::ActionRole);
    QPushButton *tp = msg.addButton("Two Players", QMessageBox::ActionRole);

    msg.exec();

    if(msg.clickedButton() == op){
        gameMode = 0;
    }else if(msg.clickedButton() == tp){
        gameMode = 1;
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            board[y][x] = 0;
        }
    }

    board[0][0] = -2;
    board[0][1] = -3;
    board[0][2] = -4;
    board[0][3] = -5;
    board[0][4] = -6;
    board[0][5] = -4;
    board[0][6] = -3;
    board[0][7] = -2;

    board[1][0] = -1;
    board[1][1] = -1;
    board[1][2] = -1;
    board[1][3] = -1;
    board[1][4] = -1;
    board[1][5] = -1;
    board[1][6] = -1;
    board[1][7] = -1;

    board[7][0] = 2;
    board[7][1] = 3;
    board[7][2] = 4;
    board[7][3] = 5;
    board[7][4] = 6;
    board[7][5] = 4;
    board[7][6] = 3;
    board[7][7] = 2;

    board[6][0] = 1;
    board[6][1] = 1;
    board[6][2] = 1;
    board[6][3] = 1;
    board[6][4] = 1;
    board[6][5] = 1;
    board[6][6] = 1;
    board[6][7] = 1;

    turn = 0;
    whitePassant.clearElPassant();
    blackPassant.clearElPassant();

    whiteKingMoved = false;
    blackKingMoved = false;

    whiteLeftRookMoved = false;
    whiteRightRookMoved= false;
    blackLeftRookMoved = false;
    blackRightRookMoved= false;

    blackCastle = false;
    blackLongCastle = false;
    whiteCastle = false;
    whiteLongCastle = false;

    nextMove();
}

int Board::getPiece(int x, int y) {
    return board[y][x];
}

QVector<QPoint> Board::getMoves(int x, int y) {

    if(board[y][x]==1 || board[y][x]==-1){
        return stripCheck(x,y,Pawn::getMoves(x,y,this));
    }
    if(board[y][x]==2 || board[y][x]==-2){
        return stripCheck(x,y,Rook::getMoves(x,y,board));
    }
    if(board[y][x]==3 || board[y][x]==-3){
        return stripCheck(x,y,Knight::getMoves(x,y,board));
    }
    if(board[y][x]==4 || board[y][x] ==-4){
        return stripCheck(x,y,Bishop::getMoves(x,y,board));
    }
    if(board[y][x]==5 || board[y][x] ==-5){
        return stripCheck(x,y,Queen::getMoves(x,y,board));
    }
    if(board[y][x]==6 || board[y][x] ==-6){
        QVector<QPoint> moves = King::getMoves(x,y,this);
        return stripCheck(x,y,moves);
    }

    return QVector<QPoint>();
}

void Board::movePiece(int srcX, int srcY, int desX, int desY) {
    whitePassant.clearElPassant();
    blackPassant.clearElPassant();
    whiteLongCastle = false;
    whiteCastle = false;
    blackLongCastle = false;
    blackCastle = false;

    if(srcY==7 && srcX==0 && board[srcY][srcX]==2){
        whiteLeftRookMoved = true;
    }
    if(srcY==7 && srcX==7 && board[srcY][srcX]==2){
        whiteRightRookMoved = true;
    }
    if(srcY==0 && srcX==0 && board[srcY][srcX]==-2){
        blackLeftRookMoved = true;
    }
    if(srcY==0 && srcX==7 && board[srcY][srcX]==-2){
        blackRightRookMoved = true;
    }
    if(srcY==7 && srcX==4 && board[srcY][srcX]==6){
        whiteKingMoved = true;
    }
    if(srcY==0 && srcX==4 && board[srcY][srcX]==-6){
        blackKingMoved = true;
    }

    if(board[srcY][srcX]==-1){//is black pawn being moved
        if(srcY-desY==-2 || srcY-desY==2){//is a first double move
            if(desX-1 >= 0 && board[desY][desX-1]==1){//check left for white pawn
                int temp = board[desY-1][desX];
                board[desY-1][desX] = 1;
                board[desY][desX-1] = 0;
                board[desY][desX] = 0;

                int kingCords[2];
                findKing(true,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0],true)){
                    whitePassant.setElPassant(QPoint(desX-1,desY),QPoint(desX,desY));
                }

                board[desY-1][desX] = temp;
                board[desY][desX-1] = 1;
                board[desY][desX] = -1;
            }
            if(desX+1 < 8 && board[desY][desX+1]==1){//check right for white pawn
                int temp = board[desY-1][desX];
                board[desY-1][desX] = 1;
                board[desY][desX+1] = 0;
                board[desY][desX] = 0;

                int kingCords[2];
                findKing(true,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0],true)){
                    whitePassant.setElPassant(QPoint(desX+1,desY),QPoint(desX,desY));
                }
                board[desY-1][desX] = temp;
                board[desY][desX+1] = 1;
                board[desY][desX] = -1;
            }
        }
    }
    else if(board[srcY][srcX]==1){//is white pawn being moved
        if(srcY-desY==-2 || srcY-desY==2){//is a first double move
            if(desX-1 >= 0 && board[desY][desX-1]==-1){//check left for black pawn
                int temp = board[desY+1][desX];
                board[desY+1][desX] = -1;
                board[desY][desX-1] = 0;
                board[desY][desX] = 0;

                int kingCords[2];
                findKing(false,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0],false)){
                    blackPassant.setElPassant(QPoint(desX-1,desY),QPoint(desX,desY));
                }
                board[desY+1][desX] = temp;
                board[desY][desX-1] = -1;
                board[desY][desX] = 1;
            }
            if(desX+1 < 8 && board[desY][desX+1]==-1){//check right for black pawn
                int temp = board[desY+1][desX];
                board[desY+1][desX] = -1;
                board[desY][desX+1] = 0;
                board[desY][desX] = 0;

                int kingCords[2];
                findKing(false,kingCords);
                if(!checkForAttack(kingCords[1],kingCords[0],false)){
                    blackPassant.setElPassant(QPoint(desX+1,desY),QPoint(desX,desY));
                }
                board[desY+1][desX] = temp;
                board[desY][desX+1] = -1;
                board[desY][desX] = 1;
            }
        }
    }
    board[desY][desX] = board[srcY][srcX];
    board[srcY][srcX] = 0;
    turn++;

    if(!checkMateStalemate(turn % 2 == 0) && checkCheck(turn % 2 == 0)){//checks if white team is in check
        QMessageBox msg;
        msg.setText("Check On Black");
        msg.exec();
    }else if(!checkMateStalemate(turn % 2 == 1) && checkCheck(turn % 2 == 1)){//checks if black team is in check
        QMessageBox msg;
        msg.setText("Check On White");
        msg.exec();
    }

    nextMove();
}

int Board::getTurn() {
    return turn;
}

ElPassant Board::getWhitePassant() {
    return whitePassant;
}

ElPassant Board::getBlackPassant() {
    return blackPassant;
}

void Board::movePassant(int srcX, int srcY, QPoint victim, bool whiteTeam) {
    board[victim.y()][victim.x()] = 0;
    if(whiteTeam){
        movePiece(srcX,srcY,victim.x(),victim.y()-1);
    }else{
        movePiece(srcX,srcY,victim.x(),victim.y()+1);
    }
}

void Board::upgradePawn(int x, int y, char upgrade) {
    if(board[y][x]==1){
        switch (upgrade){
            case 'q':
                board[y][x] = 5;
                break;
            case 'b':
                board[y][x] = 4;
                break;
            case 'k':
                board[y][x] = 3;
                break;
            case 'r':
                board[y][x] = 2;
                break;
            default:
                break;
        }
    }
    else if(board[y][x]==-1){
        switch (upgrade){
            case 'q':
                board[y][x] = -5;
                break;
            case 'b':
                board[y][x] = -4;
                break;
            case 'k':
                board[y][x] = -3;
                break;
            case 'r':
                board[y][x] = -2;
                break;
            default:
                break;
        }
    }
}

bool Board::getWLR() {
    return whiteLeftRookMoved;
}

bool Board::getWRR() {
    return whiteRightRookMoved;
}

bool Board::getBLR() {
    return blackLeftRookMoved;
}

bool Board::getBRR() {
    return blackRightRookMoved;
}

bool Board::getWKing() {
    return whiteKingMoved;
}

bool Board::getBKing() {
    return blackKingMoved;
}

bool Board::checkCheck(bool whiteTeam) {
    int kingCords[2];
    findKing(whiteTeam, kingCords);

    return checkForAttack(kingCords[1],kingCords[0], whiteTeam);
}

/**
 *  Checks for ending condition of game,
 *  if team cannot make any legal moves and is in check its mate.
 *  if team cannot make any legal moves and is not in check its stalemate
 * @param whiteTeam - is whtie team the one being attacked on
 * @return 0 = no mate or stalemate, 1 = mate, 2 = stalemate
 */
int Board::checkMateStalemate(bool whiteTeam) {

    //if the team cannot make any moves that don't end up in them check and currently in check
    // then it's check mate game over
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(whiteTeam && board[y][x] > 0){
                if(!getMoves(x,y).empty()){
                    return 0;
                }
            }
            else if(!whiteTeam && board[y][x] < 0){
                if(!getMoves(x,y).empty()){
                    return 0;
                }
            }
        }
    }

    if(checkCheck(whiteTeam)){
        return 1;
    }else{
        return 2;
    }
}


bool Board::checkForAttack(int srcX, int srcY, bool whiteTeam) {


    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(board[y][x] < 0 && whiteTeam){ // if spot is a black piece and we want to check for attack on white
                if(board[y][x] == -1){
                    QVector<QPoint> moves;
                    moves.append(QPoint(x+1,y+1));
                    moves.append(QPoint(x-1,y+1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == -2){
                    QVector<QPoint> moves = Rook::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == -3){
                    QVector<QPoint> moves = Knight::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == -4){
                    QVector<QPoint> moves = Bishop::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == -5){
                    QVector<QPoint> moves = Queen::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == -6){
                    QVector<QPoint> moves;

                    moves.append(QPoint(x+1,y));
                    moves.append(QPoint(x-1,y));
                    moves.append(QPoint(x,y+1));
                    moves.append(QPoint(x,y-1));
                    moves.append(QPoint(x+1,y+1));
                    moves.append(QPoint(x-1,y+1));
                    moves.append(QPoint(x+1,y-1));
                    moves.append(QPoint(x-1,y-1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }
            }
            else if(board[y][x] > 0 && !whiteTeam){ // if spot is a white piece and we want to check for attack on black
                if(board[y][x] == 1){
                    QVector<QPoint> moves;
                    moves.append(QPoint(x+1,y-1));
                    moves.append(QPoint(x-1,y-1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == 2){
                    QVector<QPoint> moves = Rook::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == 3){
                    QVector<QPoint> moves = Knight::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == 4){
                    QVector<QPoint> moves = Bishop::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == 5){
                    QVector<QPoint> moves = Queen::getMoves(x,y,board);

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board[y][x] == 6){
                    QVector<QPoint> moves;

                    moves.append(QPoint(x+1,y));
                    moves.append(QPoint(x-1,y));
                    moves.append(QPoint(x,y+1));
                    moves.append(QPoint(x,y-1));
                    moves.append(QPoint(x+1,y+1));
                    moves.append(QPoint(x-1,y+1));
                    moves.append(QPoint(x+1,y-1));
                    moves.append(QPoint(x-1,y-1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Board::isBlackLongCastle() const {
    return blackLongCastle;
}

void Board::setBlackLongCastle(bool blackLongCastle) {
    Board::blackLongCastle = blackLongCastle;
}

bool Board::isBlackCastle() const {
    return blackCastle;
}

void Board::setBlackCastle(bool blackCastle) {
    Board::blackCastle = blackCastle;
}

bool Board::isWhiteLongCastle() const {
    return whiteLongCastle;
}

void Board::setWhiteLongCastle(bool whiteLongCastle) {
    Board::whiteLongCastle = whiteLongCastle;
}

bool Board::isWhiteCastle() const {
    return whiteCastle;
}

void Board::setWhiteCastle(bool whiteCastle) {
    Board::whiteCastle = whiteCastle;
}

void Board::moveCastling(int type) {

    if(type == 1){//white long
        board[7][2] = 6;
        board[7][4] = 0;
        board[7][3] = 2;
        board[7][0] = 0;
        turn++;
        nextMove();
    }else if(type == 2){//white
        board[7][6] = 6;
        board[7][4] = 0;
        board[7][5] = 2;
        board[7][7] = 0;
        turn++;
        nextMove();
    }else if(type == 3){//black long
        board[0][2] = -6;
        board[0][4] =  0;
        board[0][3] = -2;
        board[0][0] =  0;
        turn++;
        nextMove();
    }else if(type == 4){//black
        board[0][6] = -6;
        board[0][4] =  0;
        board[0][5] = -2;
        board[0][7] =  0;
        turn++;
        nextMove();
    }
}

void Board::findKing(bool whiteTeam, int cords[2]) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(whiteTeam && board[y][x]==6){
                cords[0] = y;
                cords[1] = x;
                return;
            }else if(!whiteTeam && board[y][x]==-6){
                cords[0] = y;
                cords[1] = x;
                return;
            }
        }
    }
}

QVector<QPoint> Board::stripCheck(int x, int y,QVector<QPoint> moves) {
    QVector<QPoint> strippedMoves;
    bool whiteTeam = true;

    if(board[y][x] < 0){
        whiteTeam = false;
    }else if(board[y][x] == 0){
        return strippedMoves;
    }

    int kingCords[2];

    for(QPoint move: moves){
        int temp = board[move.y()][move.x()];
        board[move.y()][move.x()] = board[y][x];
        board[y][x] = 0;

        findKing(whiteTeam, kingCords);
        bool check = checkForAttack(kingCords[1],kingCords[0],whiteTeam);

        if(!check){
            strippedMoves.append(move);
        }

        board[y][x] = board[move.y()][move.x()];
        board[move.y()][move.x()] = temp;
    }

    return strippedMoves;
}

void Board::nextMove() {
    if(gameMode == 0){ //one player game, therefore need to do ai to choose black move
        if(turn%2 == 1){
            int move[4];
            alphaBeta.findMove(this,false,move);
            movePiece(move[0],move[1],move[2],move[3]);
        }
    }else if(gameMode == 1){ //two player game, let other player choose move
        return;
    }
    if(windowSet){
        window->repaint();
    }
}

void Board::setWindow(QWidget *window) {
    this->window = window;
    windowSet = true;
}
