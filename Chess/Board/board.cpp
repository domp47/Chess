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

 /**
  * Creates an instance of the game board
  *
  * @param controller game controller
  */
Board::Board(Controller* controller) {
    this->controller = controller;
}

/**
 * Initiliazes the board for a new game
 */
void Board::defaultInit(){

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
}

/**
 * Sets the board up to the specified pieces for a new game
 * @param filename CSV file containing piece information
 */
void Board::customInit(std::string filename){
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            board[y][x] = 0;
        }
    }

    std::ifstream in(filename);
    std::vector<QStringList> rows;

    //reads file row by row then splits it into a vector of lists to fill the board with
    std::string str;
    while(std::getline(in, str)){
        QStringList cols = QString::fromStdString(str).replace(" ", "").split(",");

        if(cols.size() != 8){
            throw std::runtime_error("Chess boards must have 8 columns");
        }

        rows.push_back(cols);
    }

    if(rows.size() != 8){
        throw std::runtime_error("Chess boards must have 8 rows");
    }

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {

            int piece = rows[y][x].toInt();

            if(piece < -6 || piece > 6){
                throw std::runtime_error("Unknown piece with value: " + std::to_string(piece));
            }

            board[y][x] = piece;
        }
    }

    whitePassant.clearElPassant();
    blackPassant.clearElPassant();

    whiteKingMoved = false;
    blackKingMoved = false;

    whiteLeftRookMoved = false;
    whiteRightRookMoved= false;
    blackLeftRookMoved = false;
    blackRightRookMoved= false;
}

/**
 * Gets the piece at x,y on the board
 * 
 * @param x X location of piece
 * @param y Y location of piece
 * @return piece
 */
int Board::getPiece(int x, int y) {
    return board[y][x];
}

/**
 *  Sets the piece given at the given location on the board
 * 
 * @param x X location
 * @param y Y location
 * @param val Value to set
 */
void Board::setPiece(int x, int y, int val){
    board[y][x] = val;
}

/**
 *  Get the white passant for the board
 * 
 * @return Passant
 */
ElPassant Board::getWhitePassant() {
    return whitePassant;
}

/**
 * Get the black passant for the board
 * 
 * @return Passant
 */
ElPassant Board::getBlackPassant() {
    return blackPassant;
}

/**
 *  Upgrades the pawn on position x,y to the given piece
 * 
 * @param x X location
 * @param y Y location
 * @param upgrade Piece to upgrade to
 */
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

/**
 * Gets whether the white left rook has moved
 * 
 * @return bool 
 */
bool Board::getWLR() {
    return whiteLeftRookMoved;
}

/**
 * Gets whether the white right rook has moved
 * 
 * @return bool 
 */
bool Board::getWRR() {
    return whiteRightRookMoved;
}

/**
 * Gets whether the black left rook has moved
 * 
 * @return bool 
 */
bool Board::getBLR() {
    return blackLeftRookMoved;
}

/**
 * Gets whether the black right rook has moved
 * 
 * @return bool 
 */
bool Board::getBRR() {
    return blackRightRookMoved;
}

/**
 * Gets whether the white king has moved
 * 
 * @return bool 
 */
bool Board::getWKing() {
    return whiteKingMoved;
}

/**
 * Gets whether the black king has moved
 * 
 * @return bool 
 */
bool Board::getBKing() {
    return blackKingMoved;
}

/**
 *  Sets whether the white left rook has moved
 * 
 * @param val bool
 */
void Board::setWLR(bool val) {
    whiteLeftRookMoved = val;
}

/**
 *  Sets whether the white right rook has moved
 * 
 * @param val bool
 */
void Board::setWRR(bool val) {
    whiteRightRookMoved = val;
}

/**
 *  Sets whether the black left rook has moved
 * 
 * @param val bool
 */
void Board::setBLR(bool val) {
    blackLeftRookMoved = val;
}

/**
 *  Sets whether the black right rook has moved
 * 
 * @param val bool
 */
void Board::setBRR(bool val) {
    blackRightRookMoved = val;
}

/**
 *  Sets whether the white king has moved
 * 
 * @param val bool
 */
void Board::setWKing(bool val) {
    whiteKingMoved = val;
}

/**
 *  Sets whether the black king has moved
 * 
 * @param val bool
 */
void Board::setBKing(bool val) {
    blackKingMoved = val;
}

/**
 *  Returns the board as a 2D array
 * 
 * @return board
 */
std::array<std::array<int,8>,8> Board::getBoard() {
    return board;
}

/**
 *  finds the king of the specified team
 * 
 * @param whiteTeam white team or black teams king
 * @param cords cords of the king
 */
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

/**
 *  Sets the passant for the board
 * 
 * @param white white team or black team
 * @param attacker attackers position
 * @param victim victims position
 */
void Board::setPassant(bool white, QPoint attacker, QPoint victim) {
    if(white){
        whitePassant.setElPassant(attacker, victim);
    }else{
        blackPassant.setElPassant(attacker,victim);
    }
}

/**
 *  Clears the passant on the board
 * 
 * @param white whether white passant or black passant
 */
void Board::clearPassant(bool white) {
    if(white){
        whitePassant.clearElPassant();
    }else{
        blackPassant.clearElPassant();
    }
}

/**
 * Prints the board to standard output
 */
void Board::printBoard() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            int piece = board[y][x];

            if(piece < 0){
                std::cout << piece << " ";
            }else{
                std::cout << " " << piece << " ";
            }
        }
        std::cout << std::endl;
    }
}

/**
 *  Sets the boards passant
 * 
 * @param white white team or black team
 * @param passant passant to set
 */
void Board::setPassant(bool white, ElPassant passant) {
    if(white){
        this->whitePassant = passant;
    }else{
        this->blackPassant = passant;
    }
}

/**
 * resets the save file and gameplay
 * @param filename to save the pgn file to
 */
void Board::setupSave(QString filename) {
    saveFile = filename;
    gamePlay = "";
}

/**
 * Adds move to the gameplay string
 *
 * The move consists of the move the white and black team made
 *
 * @param moveNum PGN move number
 * @param move locations of both moves in PGN format
 */
void Board::addMove(int moveNum, QString move) {
    if(moveNum == -1){
        gamePlay += " " + move;
    }else{
        gamePlay += QString::number(moveNum) + ". " + move + " ";
    }
}

/**
 * Writes the game play string to the specified file when setup.
 * If no file was specified in setup then the game play is not saved.
 */
void Board::saveGame() {
    if(saveFile != ""){
        std::ofstream out;
        out.open(saveFile.toStdString());
        out << gamePlay.toStdString() << '\n';
        out.close();
    }
}

Board *Board::createCopy() {
    auto* b = new Board(this->controller);

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            b->setPiece(x, y, this->getPiece(x, y));
        }
    }

    b->setPassant(true, this->whitePassant);
    b->setPassant(false, this->blackPassant);

    b->setWLR(this->whiteLeftRookMoved);
    b->setWRR(this->whiteRightRookMoved);
    b->setBLR(this->blackLeftRookMoved);
    b->setBRR(this->blackRightRookMoved);
    b->setWKing(this->whiteKingMoved);
    b->setBKing(this->blackKingMoved);

    return b;
}
