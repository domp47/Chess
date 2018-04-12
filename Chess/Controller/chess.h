#ifndef PROJECT_CHESS_H
#define PROJECT_CHESS_H


#include <thread>
#include "controller.h"
#include <QString>
#include <QMessageBox>

class Chess : public QObject{

    Q_OBJECT

public:
    Chess();
    void playChess();

private:
    Controller* controller;
    std::thread gameThread;

public slots:
    void gameFinished(QString endResult);
};


#endif //PROJECT_CHESS_H
