#include "chess.h"

Chess::Chess(int searchDepth) {
    controller = new Controller(searchDepth);

    connect(controller, SIGNAL(sendEOG(QString)), this, SLOT(gameFinished(QString)));
}

Chess::~Chess() {
    controller->getWindow()->close();
    gameThread.detach();
    pthread_cancel(pThread);
}

void Chess::playChess() {
    controller->playGame();

    gameThread = std::thread(&Controller::startGame, controller);
    pThread = gameThread.native_handle();
}

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
    }
}
