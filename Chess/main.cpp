

#include "Controller/chess.h"
#include <QtWidgets/QApplication>
#include <thread>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    Chess chess;
    chess.playChess();

    return app.exec();
}