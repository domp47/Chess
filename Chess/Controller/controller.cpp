#include <thread>
#include "controller.h"
#include "AI/alphaBeta.h"

//TODO change how castling and passant are detected and moved so AI can do it as well
//TODO AI pawn promotion

Controller::Controller() {
    window = new Window(this);
    board = new Board(this);
    alphaBeta = new AlphaBeta(this);

    connect(window, SIGNAL(sendClick(int, int)), this, SLOT(recieveClick(int,int)));
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
}

int Controller::noPlayers() {
    std::cout << "Playing no players" << std::endl;

    int whiteResult = 0;
    int blackResult = 0;

    while (whiteResult==0 && blackResult==0) {//keep taking turns until stalemate or checkmate

        if(turn%2==0){
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            QVector<int> move = alphaBeta->findMove(true);

            if(move.length() == 4){
                movePiece(move[0],move[1],move[2],move[3]);
                window->repaint();
            }else{
                std::cout << "Error finding piece for white team" << std::endl;
            }
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            QVector<int> move = alphaBeta->findMove(false);

            if(move.length() == 4){
                movePiece(move[0],move[1],move[2],move[3]);
                window->repaint();
            }else{
                std::cout << "Error finding piece for black team" << std::endl;
            }
        }



//        if(checkMateStalemate(true)==0 && checkCheck(true)){//checks if white team is in check
//            emit sendMessage("Check On White");
//        }else if(checkMateStalemate(false)==0 && checkCheck(false)){//checks if black team is in check
//            emit sendMessage("Check On Black");
//        }

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
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            QVector<int> move = alphaBeta->findMove(false);

            if(move.length() == 4){
                movePiece(move[0],move[1],move[2],move[3]);


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

void Controller::recieveClick(int x, int y) {
    if(needInput){
        int prevX = highlightedPiece.x();
        int prevY = highlightedPiece.y();

        if(prevY==-1 && prevX==-1){ //if nothing previously selected its on highlight piece state
            if( (board->getPiece(x,y)>0 && turn%2==0) || (board->getPiece(x,y)<0 && turn%2==1) ) {
                highlightedPiece = QPoint(x, y);
                possibleMoves = getMoves(x, y);
                window->repaint();
            }
        }else if(prevY==y && prevX==x){ //if clicking same piece deselect piece
            highlightedPiece = QPoint(-1,-1);
            possibleMoves.clear();
            window->repaint();
        }else if(isMovePossible(QPoint(x,y))){ //checks possible regular moves and moves to that piece
            /**
            if((board->getPiece(highlightedPiece.x(),highlightedPiece.y())==1 && y==0) || (board->getPiece(highlightedPiece.x(),highlightedPiece.y())==-1 && y==7)) {
                bool correctInput = false;
                char upgrade = '0';

                while (!correctInput) {
                    QString response = QInputDialog::getText(window, "Pawn Promotion",
                                                             "Enter: Q for queen, B for bishop, K for knight, R for rook.");

                    if (response == "q" || response == "Q") {
                        upgrade = 'q';
                        correctInput = true;
                    } else if (response == "b" || response == "B") {
                        upgrade = 'b';
                        correctInput = true;
                    } else if (response == "k" || response == "K") {
                        upgrade = 'k';
                        correctInput = true;
                    } else if (response == "r" || response == "R") {
                        upgrade = 'r';
                        correctInput = true;
                    }
                }


                board->upgradePawn(highlightedPiece.x(),highlightedPiece.y(),upgrade);
            }**/

            movePiece(highlightedPiece.x(),highlightedPiece.y(),x,y);
            highlightedPiece = QPoint(-1,-1);
            possibleMoves.clear();
            window->repaint();

            inputGot = true;
//            mutex.unlock();
//            waitForInput.wakeAll();
        }
        /**else if(turn%2==0 && board->getWhitePassant().getPresent()){ //if its white persons turn and there is a passant
            //check if the passant spot was clicked
            if(board->getWhitePassant().getVictim().x()==x && board->getWhitePassant().getVictim().y()-1==y){
                movePassant(highlightedPiece.x(),highlightedPiece.y(),board->getWhitePassant().getVictim(), true);
                highlightedPiece = QPoint(-1,-1);
                possibleMoves.clear();
                window->repaint();

                inputGot = true;
//                mutex.unlock();
//                waitForInput.wakeAll();
            }
        }**/
        /**else if(turn%2==1 && board->getBlackPassant().getPresent()){ //if its black persons turn and there is a passant
            if(board->getBlackPassant().getVictim().x()==x && board->getBlackPassant().getVictim().y()+1==y){
                movePassant(highlightedPiece.x(),highlightedPiece.y(),board->getBlackPassant().getVictim(), false);
                highlightedPiece = QPoint(-1,-1);
                possibleMoves.clear();
                window->repaint();

                inputGot = true;
//                mutex.unlock();
//                waitForInput.wakeAll();
            }
        }**/
        /**    //if white knight is highlighted and there is a white castle move possible
        else if(board->getPiece(highlightedPiece.x(),highlightedPiece.y())==6 && (board->isWhiteCastle() || board->isWhiteLongCastle())){
            if(board->isWhiteLongCastle() && y==7 && x==2){
                board->moveCastling(1);
                highlightedPiece = QPoint(-1,-1);
                possibleMoves.clear();
                window->repaint();

                inputGot = true;
//                mutex.unlock();
//                waitForInput.wakeAll();
            }else if(board->isWhiteCastle() && y==7 && x==6){
                board->moveCastling(2);
                highlightedPiece = QPoint(-1,-1);
                possibleMoves.clear();
                window->repaint();

                inputGot = true;
//                mutex.unlock();
//                waitForInput.wakeAll();
            }
        }**/
        /**    //if black knight is highlighted and there is a black castle move possible
        else if(board->getPiece(highlightedPiece.x(),highlightedPiece.y())==-6 && (board->isBlackCastle() || board->isBlackLongCastle())){
            if(board->isBlackLongCastle() && y==0 && x==2){
                board->moveCastling(3);
                highlightedPiece = QPoint(-1,-1);
                possibleMoves.clear();
                window->repaint();

                inputGot = true;
//                mutex.unlock();
//                waitForInput.wakeAll();
            }else if(board->isBlackCastle() && y==0 && x==6){
                board->moveCastling(4);
                highlightedPiece = QPoint(-1,-1);
                possibleMoves.clear();
                window->repaint();

                inputGot = true;
//                mutex.unlock();
//                waitForInput.wakeAll();
            }
        }**/
            //if it's another of the same piece highlight that one instead
        else if( (board->getPiece(x,y)>0 && turn%2==0) || (board->getPiece(x,y)<0 && turn%2==1) ){
            highlightedPiece = QPoint(x,y);
            possibleMoves = getMoves(x,y);
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
        QVector<QPoint> moves = King::getMoves(x,y,board->getBoard());
        return stripCheck(x,y,moves);
    }

    return QVector<Move>();
}

void Controller::movePiece(int srcX, int srcY, int desX, int desY) {
    board->clearPassant(true);
    board->clearPassant(false);

    board->setWhiteLongCastle(false);
    board->setWhiteCastle(false);
    board->setBlackLongCastle(false);
    board->setBlackCastle(false);

    if(srcY==7 && srcX==0 && board->getPiece(srcX,srcY)==2){
        board->setWLR(true);
    }
    if(srcY==7 && srcX==7 && board->getPiece(srcX,srcY)==2){
        board->setWRR(true);
    }
    if(srcY==0 && srcX==0 && board->getPiece(srcX,srcY)==-2){
        board->setBLR(true);
    }
    if(srcY==0 && srcX==7 && board->getPiece(srcX,srcY)==-2){
        board->setBRR(true);
    }
    if(srcY==7 && srcX==4 && board->getPiece(srcX,srcY)==6){
        board->setWKing(true);
    }
    if(srcY==0 && srcX==4 && board->getPiece(srcX,srcY)==-6){
        board->setBKing(true);
    }

    if(board->getPiece(srcX,srcY)==-1){//is black pawn being moved
        if(srcY-desY==-2 || srcY-desY==2){//is a first double move
            if(desX-1 >= 0 && board->getPiece(desX-1,desY)==1){//check left for white pawn
                int temp = board->getPiece(desX,desY-1);

                board->setPiece(desX,desY-1, 1);
                board->setPiece(desX-1,desY, 0);
                board->setPiece(desX,desY, 0);

                int kingCords[2];
                board->findKing(true,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0], true)){
                    board->setPassant(true,QPoint(desX-1,desY),QPoint(desX,desY));
                }

                board->setPiece(desX,desY-1, temp);
                board->setPiece(desX-1,desY, 1);
                board->setPiece(desX,desY, -1);
            }
            if(desX+1 < 8 && board->getPiece(desX+1,desY)==1){//check right for white pawn
                int temp = board->getPiece(desX,desY-1);;

                board->setPiece(desX,desY-1, 1);
                board->setPiece(desX+1,desY, 0);
                board->setPiece(desX,desY, 0);

                int kingCords[2];
                board->findKing(true,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0], true)){
                    board->setPassant(true,QPoint(desX+1,desY),QPoint(desX,desY));
                }

                board->setPiece(desX,desY-1, temp);
                board->setPiece(desX+1,desY, 1);
                board->setPiece(desX,desY, -1);
            }
        }
    }
    else if(board->getPiece(srcX,srcY)==1){//is white pawn being moved
        if(srcY-desY==-2 || srcY-desY==2){//is a first double move
            if(desX-1 >= 0 && board->getPiece(desX-1,desY)==-1){//check left for black pawn
                int temp = board->getPiece(desX,desY-1);

                board->setPiece(desX,desY+1, -1);
                board->setPiece(desX-1,desY, 0);
                board->setPiece(desX,desY, 0);

                int kingCords[2];
                board->findKing(false,kingCords);

                if(!checkForAttack(kingCords[1],kingCords[0], false)){
                    board->setPassant(false,QPoint(desX-1,desY),QPoint(desX,desY));
                }

                board->setPiece(desX,desY+1, temp);
                board->setPiece(desX-1,desY, -1);
                board->setPiece(desX,desY, 1);
            }
            if(desX+1 < 8 && board->getPiece(desX+1,desY)==-1){//check right for black pawn
                int temp = board->getPiece(desX,desY+1);

                board->setPiece(desX,desY+1, -1);
                board->setPiece(desX+1,desY, 0);
                board->setPiece(desX,desY, 0);

                int kingCords[2];
                board->findKing(false,kingCords);
                if(!checkForAttack(kingCords[1],kingCords[0], false)){
                    board->setPassant(false,QPoint(desX+1,desY),QPoint(desX,desY));
                }

                board->setPiece(desX,desY+1, temp);
                board->setPiece(desX+1,desY, -1);
                board->setPiece(desX,desY, 1);
            }
        }
    }
    board->setPiece(desX,desY, board->getPiece(srcX,srcY));
    board->setPiece(srcX,srcY,0);
}

void Controller::movePassant(int srcX, int srcY, QPoint victim, bool whiteTeam) {
    board->setPiece(victim.x(),victim.y(),0);
    if(whiteTeam){
        movePiece(srcX,srcY,victim.x(),victim.y()-1);
    }else{
        movePiece(srcX,srcY,victim.x(),victim.y()+1);
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
                    QVector<QPoint> moves = Rook::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -3){
                    QVector<QPoint> moves = Knight::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -4){
                    QVector<QPoint> moves = Bishop::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -5){
                    QVector<QPoint> moves = Queen::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == -6){
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
            else if(board->getPiece(x,y) > 0 && !whiteTeam){ // if spot is a white piece and we want to check for attack on black
                if(board->getPiece(x,y) == 1){
                    QVector<QPoint> moves;
                    moves.append(QPoint(x+1,y-1));
                    moves.append(QPoint(x-1,y-1));

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 2){
                    QVector<QPoint> moves = Rook::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 3){
                    QVector<QPoint> moves = Knight::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 4){
                    QVector<QPoint> moves = Bishop::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 5){
                    QVector<QPoint> moves = Queen::getMoves(x,y,board->getBoard());

                    if(moves.contains(QPoint(srcX,srcY))){
                        return true;
                    }
                }else if(board->getPiece(x,y) == 6){
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
QVector<QPoint> Controller::stripCheck(int x, int y,QVector<Move> moves) {
    QVector<QPoint> strippedMoves;
    bool whiteTeam = true;

    if(board->getPiece(x,y) < 0){
        whiteTeam = false;
    }else if(board->getPiece(x,y) == 0){
        return strippedMoves;
    }

    int kingCords[2];

    for(QPoint move: moves){
        int temp = board->getPiece(move.x(),move.y());
        board->setPiece(move.x(),move.y(), board->getPiece(x,y));
        board->setPiece(x,y,0);

        board->findKing(whiteTeam, kingCords);
        bool check = checkForAttack(kingCords[1],kingCords[0], whiteTeam);

        if(!check){
            strippedMoves.append(move);
        }

        board->setPiece(x,y,board->getPiece(move.x(),move.y()));
        board->setPiece(move.x(),move.y(),temp);
    }

    return strippedMoves;
}

QPoint Controller::getHighlighted() {
    return highlightedPiece;
}
