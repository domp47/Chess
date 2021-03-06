#ifndef PROJECT_CHESS_H
#define PROJECT_CHESS_H


#include <thread>
#include "controller.h"
#include <QString>
#include <QMessageBox>

class Chess : public QObject{

    Q_OBJECT

public:
    Chess(int searchDepth, std::string graphPath, std::string checkpointPath);
    ~Chess();
    void playChess();

private:
    Controller* controller;
    std::thread gameThread;
    pthread_t pThread;
    bool cleanExit;

public slots:
    void gameFinished(QString endResult);
};


#endif //PROJECT_CHESS_H
