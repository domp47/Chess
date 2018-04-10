

#include "Controller/controller.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    Controller* controller = new Controller();

    return app.exec();
}