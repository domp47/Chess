#include "chess.h"

/**
 *  Creates new chess game with specified search depth
 * 
 * @param searchDepth depth of alpha beta searching
 */
Chess::Chess(int searchDepth, std::string graphPath, std::string checkpointPath) {
    controller = new Controller(searchDepth, graphPath, checkpointPath);

    cleanExit = false;

    connect(controller, SIGNAL(sendEOG(QString)), this, SLOT(gameFinished(QString)));
}

/**
 * destroys thread if still active
 */
Chess::~Chess() {
    controller->getWindow()->close();

    if(!cleanExit){
        gameThread.detach();
        pthread_cancel(pThread);
    }
}

/**
 * starts a game of chess
 */
void Chess::playChess() {
    controller->playGame();

    gameThread = std::thread(&Controller::startGame, controller);
    pThread = gameThread.native_handle();
}

/**
 *  Called once the game is finished, used to choose whether
 *  to start a new game or exit the program
 * 
 * @param endResult result of previous game
 */
void Chess::gameFinished(QString endResult) {
    QMessageBox annoucement;
    annoucement.setText(endResult);
    QPushButton *ng = annoucement.addButton("New Game", QMessageBox::ActionRole);
    QPushButton *end = annoucement.addButton("Exit", QMessageBox::NoRole);

    annoucement.exec();

    if(annoucement.clickedButton() == ng){
        gameThread.join();

        controller->playGame();

        gameThread = std::thread(&Controller::startGame, controller);
        pThread = gameThread.native_handle();

    }else if(annoucement.clickedButton() == end){
        gameThread.join();

        controller->getWindow()->close();

        cleanExit = true;
    }
}
