#ifndef Controller_H
#define Controller_H

#include <GUI/window.h>
//#include <Board/board.h>
#include <mutex>
#include <condition_variable>
#include "move.h"
#include "RepresentationMap.h"
#include <QCheckBox>
#include <QFileDialog>
#include <QDebug>
//#include "Board/board.h"
//#include "AI/alphaBeta.h"

class AlphaBeta;
class Board;

class Controller : public QObject{

    Q_OBJECT

public:
    Controller(int searchDepth, std::string graphPath, std::string checkpointPath);
    Window* getWindow();
    Board* getBoard();
    int checkMateStalemate(bool whiteTeam);
    void movePiece(Move move);
    QVector<Move> getMoves(int x, int y);
    bool checkCheck(bool whiteTeam);
    bool checkForAttack(int x, int y, bool whiteTeam);
    void playGame();
    QVector<Move> getPossibleMoves();
    QPoint getHighlighted();
    void startGame();
private:
    QVector<Move> stripCheck(int x, int y, QVector<Move> moves);
    int noPlayers();
    int onePlayer();
    int twoPlayers();
    bool isMovePossible(QPoint p);
    bool checkVectorOfMoves(QVector<Move> moves, int x, int y);
    QString PGNmove(Move move);
private:
    Window* window;
    Board* board;
    AlphaBeta* alphaBeta;
    std::mutex mutex;
    std::condition_variable cv;
    bool needInput;
    int turn;
    QPoint highlightedPiece;
    QVector<Move> possibleMoves;
    RepresentationMap* repSwap;
    int gamemode;
    QString humanMove;
public slots:
    void receiveClick(int x, int y);
    void receivePawnPromotion(char choice, int x, int y);
signals:
    void sendMessage(QString message);
    void sendEOG(QString result);
    void sendPawnPromotion(int x, int y);
};

#endif