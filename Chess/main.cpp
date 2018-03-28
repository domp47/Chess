

#include <GUI/window.h>
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    Board* b = new Board();

    Window* w = new Window(b);
    w->show();

    return app.exec();
}