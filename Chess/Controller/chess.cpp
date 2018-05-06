#include "chess.h"

Chess::Chess() {
    controller = new Controller();

    connect(controller, SIGNAL(sendEOG(QString)), this, SLOT(gameFinished(QString)));
}

void Chess::playChess() {
    controller->playGame();

    gameThread = std::thread(&Controller::startGame, controller);
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


    }else if(annoucement.clickedButton() == end){
        gameThread.join();

        controller->getWindow()->close();
    }
}
