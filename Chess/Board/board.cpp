#include <chrono>
#include <thread>
#include "board.h"
#include "Controller/controller.h"
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

Board::Board(Controller* controller) {
    this->controller = controller;

    board = new int*[8];
    for (int i = 0; i < 8; ++i) {
        board[i] = new int[8];
    }
}

void Board::initBoard(){

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
}

int Board::getPiece(int x, int y) {
    return board[y][x];
}

void Board::setPiece(int x, int y, int val){
    board[y][x] = val;
}

ElPassant Board::getWhitePassant() {
    return whitePassant;
}

ElPassant Board::getBlackPassant() {
    return blackPassant;
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

void Board::setWLR(bool val) {
    whiteLeftRookMoved = val;
}

void Board::setWRR(bool val) {
    whiteRightRookMoved = val;
}

void Board::setBLR(bool val) {
    blackLeftRookMoved = val;
}

void Board::setBRR(bool val) {
    blackRightRookMoved = val;
}

void Board::setWKing(bool val) {
    whiteKingMoved = val;
}

void Board::setBKing(bool val) {
    blackKingMoved = val;
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
    }else if(type == 2){//white
        board[7][6] = 6;
        board[7][4] = 0;
        board[7][5] = 2;
        board[7][7] = 0;
    }else if(type == 3){//black long
        board[0][2] = -6;
        board[0][4] =  0;
        board[0][3] = -2;
        board[0][0] =  0;
    }else if(type == 4){//black
        board[0][6] = -6;
        board[0][4] =  0;
        board[0][5] = -2;
        board[0][7] =  0;
    }
}

int **Board::getBoard() {
    return board;
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

void Board::setPassant(bool white, QPoint attacker, QPoint victim) {
    if(white){
        whitePassant.setElPassant(attacker, victim);
    }else{
        blackPassant.setElPassant(attacker,victim);
    }
}

void Board::clearPassant(bool white) {
    if(white){
        whitePassant.clearElPassant();
    }else{
        blackPassant.clearElPassant();
    }
}
