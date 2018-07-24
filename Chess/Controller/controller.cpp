#include <thread>
#include "controller.h"
#include "AI/alphaBeta.h"
#include "Board/board.h"

//TODO AI pawn promotion

Controller::Controller() {
    window = new Window(this);
    board = new Board(this);
    alphaBeta = new AlphaBeta(this);

    connect(window, SIGNAL(sendPawnPromotion(char, int, int)), this, SLOT(receivePawnPromotion(char, int, int)));
    connect(window, SIGNAL(sendClick(int, int)), this, SLOT(receiveClick(int, int)));
}

void Controller::startGame(){

    int result = -1;

    if (gamemode == 0) {
        result = onePlayer();
    } else if (gamemode == 1) {
        result = twoPlayers();
    } else if (gamemode == 2) {
        result = noPlayers();
    }

    if(result == 0){
        emit sendEOG("It's a Draw");
    }else if(result == 1){
        emit sendEOG("White Team Wins");
    }else if(result == 2){
        emit sendEOG("Black Team Wins");
    }else{
        emit sendEOG("Error");
    }
}

void Controller::playGame() {
    possibleMoves.clear();
    highlightedPiece = QPoint(-1,-1);
    turn = 0;
    board->initBoard();

    window->updateCache(board->getBoard());

    QMessageBox msg;
    msg.setText("Choose a game mode");
    QPushButton *np = msg.addButton("No Players", QMessageBox::ActionRole);
    QPushButton *op = msg.addButton("One Player", QMessageBox::ActionRole);
    QPushButton *tp = msg.addButton("Two Players", QMessageBox::ActionRole);

    msg.exec();

    if (msg.clickedButton() == op) {
        gamemode = 0;
    } else if (msg.clickedButton() == tp) {
        gamemode = 1;
    } else if (msg.clickedButton() == np) {
        gamemode = 2;
    }

    window->show();
    window->repaint();
}

int Controller::noPlayers() {
    std::cout << "Playing no players" << std::endl;

    int whiteResult = 0;
    int blackResult = 0;

    while (whiteResult==0 && blackResult==0) {//keep taking turns until stalemate or checkmate

        if(turn%2==0){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            Move move = alphaBeta->findMove(true);

            if(move.end.x() != -1){
                movePiece(move);
                window->updateCache(board->getBoard());
                window->repaint();


                std::cout << "White Move: " << (char)(65 + move.init.x()) << (8 - move.init.y()) << " -> " << (char)(65 + move.end.x()) << (8 - move.end.y()) << std::endl;
            }else{
                std::cout << "Error finding piece for white team" << std::endl;
            }
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            Move move = alphaBeta->findMove(false);

            if(move.end.x() != -1){
                movePiece(move);
                window->updateCache(board->getBoard());
                window->repaint();

                std::cout << "Black Move: " << (char)(65 + move.init.x()) << (8 - move.init.y()) << " -> " << (char)(65 + move.end.x()) << (8 - move.end.y()) << std::endl;
            }else{
                std::cout << "Error finding piece for black team" << std::endl;
            }
        }

        turn++;

        whiteResult = checkMateStalemate(true);
        blackResult = checkMateStalemate(false);
    }

    if(whiteResult == 1){
        return 2;
    }else if(blackResult == 1){
        return 1;
    }else if(whiteResult == 2 || blackResult == 2){
        return 0;
    }

    return -1;
}

int Controller::onePlayer() {
    std::cout << "Playing one player" << std::endl;

    int whiteResult = 0;
    int blackResult = 0;

    while (whiteResult==0 && blackResult==0) {//keep taking turns until stalemate or checkmate

        if(turn%2==0){//white team turn
            needInput = true;

//            mutex.lock(); //TODO figure out why this isnt unlocking properly
//            waitForInput.wait(&mutex);
            inputGot = false;
            while (!inputGot){
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }


            needInput = false;
        }else{//black persons turn
//            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            Move move = alphaBeta->findMove(false);

            if(move.end.x() != -1){
                movePiece(move);
                window->updateCache(board->getBoard());
                window->repaint();
            }else{
                std::cout << "Error finding piece for black team" << std::endl;
            }
        }

        if(checkMateStalemate(true)==0 && checkCheck(true)){//checks if white team is in check
            emit sendMessage("Check On White");
        }else if(checkMateStalemate(false)==0 && checkCheck(false)){//checks if black team is in check
            emit sendMessage("Check On Black");
        }

        turn++;

        whiteResult = checkMateStalemate(true);
        blackResult = checkMateStalemate(false);
    }

    if(whiteResult == 1){
        return 2;
    }else if(blackResult == 1){
        return 1;
    }else if(whiteResult == 2 || blackResult == 2){
        return 0;
    }

    return -1;
}

/**
 *
 * @return 0 = tie or stalemate, 1 = white wins, 2 = black wins
 */
int Controller::twoPlayers() {
    std::cout << "Playing two players" << std::endl;

    int whiteResult = 0;
    int blackResult = 0;

    while (whiteResult==0 && blackResult==0){//keep taking turns until stalemate or checkmate

        needInput = true;

//        mutex.lock();
//        waitForInput.wait(&mutex);
        inputGot = false;
        while (!inputGot){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        needInput = false;

        if(checkMateStalemate(true)==0 && checkCheck(true)){//checks if white team is in check
            emit sendMessage("Check On White");
        }else if(checkMateStalemate(false)==0 && checkCheck(false)){//checks if black team is in check
            emit sendMessage("Check On Black");
        }

        turn++;

        whiteResult = checkMateStalemate(true);
        blackResult = checkMateStalemate(false);
    }

    if(whiteResult == 1){
        return 2;
    }else if(blackResult == 1){
        return 1;
    }else if(whiteResult == 2 || blackResult == 2){
        return 0;
    }

    return -1;
}

void Controller::receiveClick(int x, int y) {
    if(needInput){
        int prevX = highlightedPiece.x();
        int prevY = highlightedPiece.y();

        if(prevY==-1 && prevX==-1){ //if nothing previously selected its on highlight piece state
            if( (board->getPiece(x,y)>0 && turn%2==0) || (board->getPiece(x,y)<0 && turn%2==1) ) {
                highlightedPiece = QPoint(x, y);
                possibleMoves = getMoves(x, y);
                window->updateCache(board->getBoard(), highlightedPiece, possibleMoves);
                window->repaint();
            }
        }else if(prevY==y && prevX==x){ //if clicking same piece deselect piece
            highlightedPiece = QPoint(-1,-1);
            possibleMoves.clear();
            window->updateCache(board->getBoard(), highlightedPiece, possibleMoves);
            window->repaint();
        }else if(isMovePossible(QPoint(x,y))){ //checks possible regular moves and moves to that piece
            Move move(QPoint(-1,-1),QPoint(-1,-1));

            for(Move m: possibleMoves){
                if(m.end.x()==x && m.end.y()==y){
                    move = m;
                    break;
                }
            }

            movePiece(move);
            highlightedPiece = QPoint(-1,-1);
            possibleMoves.clear();
            window->updateCache(board->getBoard(), highlightedPiece, possibleMoves);
            window->repaint();

            inputGot = true;
//            mutex.unlock();
//            waitForInput.wakeAll();
        }
        //if it's another of the same piece highlight that one instead
        else if( (board->getPiece(x,y)>0 && turn%2==0) || (board->getPiece(x,y)<0 && turn%2==1) ){
            highlightedPiece = QPoint(x,y);
            possibleMoves = getMoves(x,y);
            window->updateCache(board->getBoard(), highlightedPiece, possibleMoves);
            window->repaint();
        }
    }

}

Window *Controller::getWindow() {
    return window;
}

Board *Controller::getBoard() {
    return board;
}

QVector<Move> Controller::getPossibleMoves() {
    return possibleMoves;
}

bool Controller::isMovePossible(QPoint p) {
    for(Move move: possibleMoves){
        if(move.end.x()==p.x() && move.end.y()==p.y())
            return true;
    }
    return false;
}

QVector<Move> Controller::getMoves(int x, int y) {
    if(board->getPiece(x,y)==1 || board->getPiece(x,y)==-1){
        return stripCheck(x,y,Pawn::getMoves(x,y,board->getBoard(), this));
    }
    if(board->getPiece(x,y)==2 || board->getPiece(x,y)==-2){
        return stripCheck(x,y,Rook::getMoves(x,y,board->getBoard()));
    }
    if(board->getPiece(x,y)==3 || board->getPiece(x,y)==-3){
        return stripCheck(x,y,Knight::getMoves(x,y,board->getBoard()));
    }
    if(board->getPiece(x,y)==4 || board->getPiece(x,y)==-4){
        return stripCheck(x,y,Bishop::getMoves(x,y,board->getBoard()));
    }
    if(board->getPiece(x,y)==5 || board->getPiece(x,y)==-5){
        return stripCheck(x,y,Queen::getMoves(x,y,board->getBoard()));
    }
    if(board->getPiece(x,y)==6 || board->getPiece(x,y)==-6){
        QVector<Move> moves = King::getMoves(x,y, this);
        moves = stripCheck(x,y,moves);
        return moves;
    }

    return {};
}

void Controller::movePiece(Move move) {
    board->clearPassant(true);
    board->clearPassant(false);

    board->setWhiteLongCastle(false);//TODO investigate if I still need this
    board->setWhiteCastle(false);
    board->setBlackLongCastle(false);
    board->setBlackCastle(false);

    if(std::abs(board->getPiece(move.init.x(),move.init.y()))==6){
        std::cout << "Moving King" << std::endl;
        std::cout << "x: " << move.init.x() << ", y: " << move.init.y() << std::endl;
        std::cout << "piece " << board->getPiece(move.init.x(),move.init.y()) << std::endl;
    }

    if(move.init.y()==7 && move.init.x()==0 && board->getPiece(move.init.x(),move.init.y())==2){
        board->setWLR(true);
    }
    else if(move.init.y()==7 && move.init.x()==7 && board->getPiece(move.init.x(),move.init.y())==2){
        board->setWRR(true);
    }
    else if(move.init.y()==0 && move.init.x()==0 && board->getPiece(move.init.x(),move.init.y())==-2){
        board->setBLR(true);
    }
    else if(move.init.y()==0 && move.init.x()==7 && board->getPiece(move.init.x(),move.init.y())==-2){
        board->setBRR(true);
    }
    else if(move.init.y()==7 && move.init.x()==4 && board->getPiece(move.init.x(),move.init.y())==6){
        board->setWKing(true);
    }
    else if(move.init.y()==0 && move.init.x()==4 && board->getPiece(move.init.x(),move.init.y())==-6){
        board->setBKing(true);
    }

    if(board->getPiece(move.init.x(),move.init.y())==-1){//is black pawn being moved
        if(move.init.y()-move.end.y()==-2 || move.init.y()-move.end.y()==2){//is a first double move
            if(move.end.x()-1 >= 0 && board->getPiece(move.end.x()-1,move.end.y())==1){//check left for white pawn
                int temp = board->getPiece(move.end.x(),move.end.y()-1);

                board->setPiece(move.end.x(),move.end.y()-1, 1);
                board->setPiece(move.end.x()-1,move.end.y(), 0);
                board->setPiece(move.end.x(),move.end.y(), 0);

                int kingCords[2];
                board->findKing(true,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0], true)){
                    board->setPassant(true,QPoint(move.end.x()-1,move.end.y()),QPoint(move.end.x(),move.end.y()));
                }

                board->setPiece(move.end.x(),move.end.y()-1, temp);
                board->setPiece(move.end.x()-1,move.end.y(), 1);
                board->setPiece(move.end.x(),move.end.y(), -1);
            }
            if(move.end.x()+1 < 8 && board->getPiece(move.end.x()+1,move.end.y())==1){//check right for white pawn
                int temp = board->getPiece(move.end.x(),move.end.y()-1);;

                board->setPiece(move.end.x(),move.end.y()-1, 1);
                board->setPiece(move.end.x()+1,move.end.y(), 0);
                board->setPiece(move.end.x(),move.end.y(), 0);

                int kingCords[2];
                board->findKing(true,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0], true)){
                    board->setPassant(true,QPoint(move.end.x()+1,move.end.y()),QPoint(move.end.x(),move.end.y()));
                }

                board->setPiece(move.end.x(),move.end.y()-1, temp);
                board->setPiece(move.end.x()+1,move.end.y(), 1);
                board->setPiece(move.end.x(),move.end.y(), -1);
            }
        }
    }
    else if(board->getPiece(move.init.x(),move.init.y())==1){//is white pawn being moved
        if(move.init.y()-move.end.y()==-2 || move.init.y()-move.end.y()==2){//is a first double move
            if(move.end.x()-1 >= 0 && board->getPiece(move.end.x()-1,move.end.y())==-1){//check left for black pawn
                int temp = board->getPiece(move.end.x(),move.end.y()-1);

                board->setPiece(move.end.x(),move.end.y()+1, -1);
                board->setPiece(move.end.x()-1,move.end.y(), 0);
                board->setPiece(move.end.x(),move.end.y(), 0);

                int kingCords[2];
                board->findKing(false,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0], false)){
                    board->setPassant(false,QPoint(move.end.x()-1,move.end.y()),QPoint(move.end.x(),move.end.y()));
                }

                board->setPiece(move.end.x(),move.end.y()+1, temp);
                board->setPiece(move.end.x()-1,move.end.y(), -1);
                board->setPiece(move.end.x(),move.end.y(), 1);
            }
            if(move.end.x()+1 < 8 && board->getPiece(move.end.x()+1,move.end.y())==-1){//check right for black pawn
                int temp = board->getPiece(move.end.x(),move.end.y()+1);

                board->setPiece(move.end.x(),move.end.y()+1, -1);
                board->setPiece(move.end.x()+1,move.end.y(), 0);
                board->setPiece(move.end.x(),move.end.y(), 0);

                int kingCords[2];
                board->findKing(false,kingCords);
                if(!checkForAttack(kingCords[1],kingCords[0], false)){
                    board->setPassant(false,QPoint(move.end.x()+1,move.end.y()),QPoint(move.end.x(),move.end.y()));
                }

                board->setPiece(move.end.x(),move.end.y()+1, temp);
                board->setPiece(move.end.x()+1,move.end.y(), -1);
                board->setPiece(move.end.x(),move.end.y(), 1);
            }
        }
    }

    if(move.special==0){
        board->setPiece(move.end.x(),move.end.y(), board->getPiece(move.init.x(),move.init.y()));
        board->setPiece(move.init.x(),move.init.y(),0);
    }else if(move.special==1){
        board->setPiece(move.end.x(),move.init.y(),0);
        board->setPiece(move.end.x(),move.end.y(), board->getPiece(move.init.x(),move.init.y()));
        board->setPiece(move.init.x(),move.init.y(),0);
    }else if(move.special==2){// castling left
        board->setPiece(2,move.init.y(),board->getPiece(4,move.init.y()));
        board->setPiece(3,move.init.y(),board->getPiece(0,move.init.y()));
        board->setPiece(0,move.init.y(),0);
        board->setPiece(4,move.init.y(),0);
    }else if(move.special==3){//castling right
        board->setPiece(6,move.init.y(),board->getPiece(4,move.init.y()));
        board->setPiece(5,move.init.y(),board->getPiece(7,move.init.y()));
        board->setPiece(7,move.init.y(),0);
        board->setPiece(4,move.init.y(),0);
    }else if(move.special==4){//pawn promotion
        if(gamemode==1 || (gamemode==0 && turn%2==0)){
            emit sendPawnPromotion(move.init.x(), move.init.y());

            board->setPiece(move.end.x(), move.end.y(), board->getPiece(move.init.x(), move.init.y()));
            board->setPiece(move.init.x(), move.init.y(), 0);
        }else{
            char upgrade = alphaBeta->findUpgrade(move);

            board->upgradePawn(move.init.x(), move.init.y(), upgrade);

            board->setPiece(move.end.x(), move.end.y(), board->getPiece(move.init.x(), move.init.y()));
            board->setPiece(move.init.x(), move.init.y(), 0);
        }
    }


}

bool Controller::checkCheck(bool whiteTeam) {
    int kingCords[2];
    board->findKing(whiteTeam, kingCords);

    return checkForAttack(kingCords[1],kingCords[0], whiteTeam);
}

/**
 *  Checks for ending condition of game,
 *  if team cannot make any legal moves and is in check its mate.
 *  if team cannot make any legal moves and is not in check its stalemate
 * @param whiteTeam - is white team the one being attacked on
 * @return 0 = no mate or stalemate, 1 = mate, 2 = stalemate
 */
int Controller::checkMateStalemate(bool whiteTeam) {

    //if the team cannot make any moves that don't end up in them check and currently in check
    // then it's check mate game over
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(whiteTeam && board->getPiece(x,y) > 0){
                if(!getMoves(x,y).empty()){
                    return 0;
                }
            }
            else if(!whiteTeam && board->getPiece(x,y) < 0){
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

bool Controller::checkForAttack(int srcX, int srcY, bool whiteTeam) {


    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(board->getPiece(x,y) < 0 && whiteTeam){ // if spot is a black piece and we want to check for attack on white
                if(board->getPiece(x,y) == -1){
                    QVector<QPoint> moves;
                    moves.append(QPoint(x+1,y+1));
                    moves.append(QPoint(x-1,y+1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -2){
                    QVector<Move> moves = Rook::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -3){
                    QVector<Move> moves = Knight::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -4){
                    QVector<Move> moves = Bishop::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -5){
                    QVector<Move> moves = Queen::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -6){
                    QVector<Move> moves;

                    moves.append(Move(QPoint(srcX,srcY),QPoint(x+1,y)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x-1,y)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x,y+1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x,y-1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x+1,y+1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x-1,y+1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x+1,y-1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x-1,y-1)));

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }
            }
            else if(board->getPiece(x,y) > 0 && !whiteTeam){ // if spot is a white piece and we want to check for attack on black
                if(board->getPiece(x,y) == 1){
                    QVector<QPoint> moves;
                    moves.append(QPoint(x+1,y-1));
                    moves.append(QPoint(x-1,y-1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 2){
                    QVector<Move> moves = Rook::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 3){
                    QVector<Move> moves = Knight::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 4){
                    QVector<Move> moves = Bishop::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 5){
                    QVector<Move> moves = Queen::getMoves(x,y,board->getBoard());

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 6){
                    QVector<Move> moves;

                    moves.append(Move(QPoint(srcX,srcY),QPoint(x+1,y)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x-1,y)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x,y+1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x,y-1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x+1,y+1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x-1,y+1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x+1,y-1)));
                    moves.append(Move(QPoint(srcX,srcY),QPoint(x-1,y-1)));

                    if(checkVectorOfMoves(moves,srcX,srcY)){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
QVector<Move> Controller::stripCheck(int x, int y,QVector<Move> moves) {
    QVector<Move> strippedMoves;
    bool whiteTeam = true;

    if(board->getPiece(x,y) < 0){
        whiteTeam = false;
    }else if(board->getPiece(x,y) == 0){
        return strippedMoves;
    }

    int kingCords[2];

    for(Move move: moves){

        int temp, king, rook;

        if(move.special==0){// normal move
            temp = board->getPiece(move.end.x(),move.end.y());
            board->setPiece(move.end.x(),move.end.y(), board->getPiece(x,y));
            board->setPiece(x,y,0);
        }else if(move.special==1){//passant move
            temp = board->getPiece(move.end.x(),move.init.y());
            board->setPiece(move.end.x(),move.init.y(),0);
            board->setPiece(move.end.x(),move.end.y(), board->getPiece(x,y));
            board->setPiece(x,y,0);
        }else if(move.special==2){// castling left
            rook = board->getPiece(0,y);
            king = board->getPiece(4,y);

            board->setPiece(0,y,0);
            board->setPiece(4,y,0);
            board->setPiece(2,y,king);
            board->setPiece(3,y,rook);
        }else if(move.special==3){//castling right
            rook = board->getPiece(7,y);
            king = board->getPiece(4,y);

            board->setPiece(7,y,0);
            board->setPiece(4,y,0);
            board->setPiece(6,y,king);
            board->setPiece(5,y,rook);
        }

        board->findKing(whiteTeam, kingCords);
        bool check = checkForAttack(kingCords[1],kingCords[0], whiteTeam);

        if(!check){
            strippedMoves.append(move);
        }

        if(move.special==0){// normal move
            board->setPiece(x,y,board->getPiece(move.end.x(),move.end.y()));
            board->setPiece(move.end.x(),move.end.y(), temp);
        }else if(move.special==1){//passant move
            board->setPiece(x,y,board->getPiece(move.end.x(),move.end.y()));
            board->setPiece(move.end.x(),move.end.y(),0);
            board->setPiece(move.end.x(),move.init.y(),temp);
        }else if(move.special==2){// castling left
            board->setPiece(2,y,0);
            board->setPiece(3,y,0);
            board->setPiece(0,y,rook);
            board->setPiece(4,y,king);
        }else if(move.special==3){//castling right
            board->setPiece(6,y,0);
            board->setPiece(5,y,0);
            board->setPiece(7,y,rook);
            board->setPiece(4,y,king);
        }

    }

    return strippedMoves;
}

QPoint Controller::getHighlighted() {
    return highlightedPiece;
}

bool Controller::checkVectorOfMoves(QVector<Move> moves, int x, int y) {
    for(Move move: moves){
        if(move.end.y()==y && move.end.x()==x){
            return true;
        }
    }
    return false;
}

void Controller::receivePawnPromotion(char choice, int x, int y) {
    board->upgradePawn(x, y, choice);
}
