#ifndef Controller_H
#define Controller_H

#include <GUI/window.h>
#include <Board/board.h>
#include <QtCore/QWaitCondition>
#include <QtCore/QMutex>
//#include "AI/alphaBeta.h"

class AlphaBeta;

class Controller : public QObject{

    Q_OBJECT

public:
    Controller();
    Window* getWindow();
    Board* getBoard();
    int checkMateStalemate(bool whiteTeam);
    void movePiece(int srcX, int srcY, int desX, int desY);
    QVector<Move> getMoves(int x, int y);
    bool checkCheck(bool whiteTeam);
    bool checkForAttack(int x, int y, bool whiteTeam);
    void playGame();
    QVector<Move> getPossibleMoves();
    QPoint getHighlighted();
    void startGame();
private:
    QVector<Move> stripCheck(int x, int y, QVector<QPoint> moves);
    int noPlayers();
    int onePlayer();
    int twoPlayers();
    bool isMovePossible(QPoint p);
private:
    Window* window;
    Board* board;
    AlphaBeta* alphaBeta;
    QMutex mutex;
    QWaitCondition waitForInput;
    bool inputGot;
    bool needInput;
    int turn;
    QPoint highlightedPiece;
    QVector<Move> possibleMoves;
    int gamemode;
public slots:
    void recieveClick(int x, int y);
signals:
    void sendMessage(QString message);
    void sendEOG(QString result);
};

#endif