#include "window.h"
#include "Controller/controller.h"
#include "Board/board.h"

Window::Window(Controller* controller) {
    this->setFixedWidth(850);
    this->setFixedHeight(850);

    this->controller = controller;
    map = new ImageMap();

    connect(controller, SIGNAL(sendMessage(QString)), this, SLOT(showMessage(QString)));
}

void Window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0,0,850,850,Colors::background());

    int highlightedX = controller->getHighlighted().x();
    int highlightedY = controller->getHighlighted().y();

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            int xLoc = (x * 100) + STARTING_X;
            int yLoc = (y * 100) + STARTING_Y;
            int size = 100;
            bool highlighted = false;

            if(y==highlightedY&&x==highlightedX){
                painter.fillRect(xLoc, yLoc,100,100,Colors::highlight());
                size -=20;
                yLoc +=10;
                xLoc +=10;
                highlighted = true;
            }
            if((x+y)%2==0)
                painter.fillRect(xLoc, yLoc,size,size,Colors::light());
            else
                painter.fillRect(xLoc, yLoc,size,size,Colors::dark());

            if(highlighted){
                xLoc -= 10;
                yLoc -= 10;
            }

            painter.drawRect(xLoc,yLoc,100,100);

            int piece = controller->getBoard()->getPiece(x, y);

            if(piece!=0){
                std::string imgLoc = map->getItem(piece);
                QImage image(QString::fromStdString(imgLoc));
                QPoint pt(xLoc+20,yLoc+20);
                painter.drawImage(pt,image);
            }
        }
    }

    for(Move m: controller->getPossibleMoves()){
        int xLoc = (m.end.x() * 100) + STARTING_X;
        int yLoc = (m.end.y() * 100) + STARTING_Y;

        if(controller->getBoard()->getPiece(m.end.x(),m.end.y())==0)
            painter.fillRect(xLoc,yLoc,100,100,Colors::move());
        else
            painter.fillRect(xLoc,yLoc,100,100,Colors::special());

        yLoc +=10;
        xLoc +=10;

        if((m.end.x()+m.end.y())%2==0)
            painter.fillRect(xLoc, yLoc,80,80,Colors::light());
        else
            painter.fillRect(xLoc, yLoc,80,80,Colors::dark());

        int piece = controller->getBoard()->getPiece(m.end.x(), m.end.y());

        xLoc -= 10;
        yLoc -= 10;

        if(piece!=0){
            std::string imgLoc = map->getItem(piece);
            QImage image(QString::fromStdString(imgLoc));
            QPoint pt(xLoc+20,yLoc+20);
            painter.drawImage(pt,image);
        }
    }

    if(highlightedY != -1 || highlightedX != -1){//if a piece is highlighted
        if(controller->getBoard()->getPiece(highlightedX,highlightedY)==-1){//black pawn
            if(controller->getBoard()->getBlackPassant().getPresent()){//passant possible

                //selected piece is one of the possible passant attacks
                if(controller->getBoard()->getBlackPassant().getAttacker1().x()==highlightedX && controller->getBoard()->getBlackPassant().getAttacker1().y()==highlightedY){
                    int x = (controller->getBoard()->getBlackPassant().getVictim().x() * 100 ) + STARTING_X;
                    int y = ((controller->getBoard()->getBlackPassant().getVictim().y() + 1) * 100) + STARTING_Y;

                    painter.fillRect(x, y,100,100,Colors::special());

                    if(((controller->getBoard()->getBlackPassant().getVictim().x())+(controller->getBoard()->getBlackPassant().getVictim().y() + 1))%2==0){
                        painter.fillRect(x+10,y+10,80,80,Colors::light());
                    }else{
                        painter.fillRect(x+10,y+10,80,80,Colors::dark());
                    }

                }
                if(controller->getBoard()->getBlackPassant().getAttacker2().x()==highlightedX && controller->getBoard()->getBlackPassant().getAttacker2().y()==highlightedY){
                    int x = (controller->getBoard()->getBlackPassant().getVictim().x() * 100 ) + STARTING_X;
                    int y = ((controller->getBoard()->getBlackPassant().getVictim().y() + 1) * 100) + STARTING_Y;

                    painter.fillRect(x, y,100,100,Colors::special());

                    if(((controller->getBoard()->getBlackPassant().getVictim().x())+(controller->getBoard()->getBlackPassant().getVictim().y() + 1))%2==0){
                        painter.fillRect(x+10,y+10,80,80,Colors::light());
                    }else{
                        painter.fillRect(x+10,y+10,80,80,Colors::dark());
                    }

                }
            }
        }
        else if(controller->getBoard()->getPiece(highlightedX,highlightedY)==1){//white pawn
            if(controller->getBoard()->getWhitePassant().getPresent()){//passant possible

                //selected piece is one of the possible passant attacks

                int attack1x = controller->getBoard()->getWhitePassant().getAttacker1().x();
                int attack1y = controller->getBoard()->getWhitePassant().getAttacker1().y();

                int attack2x = controller->getBoard()->getWhitePassant().getAttacker2().x();
                int attack2y = controller->getBoard()->getWhitePassant().getAttacker2().y();

                if(attack1x==highlightedX && attack1y==highlightedY){
                    int x = (controller->getBoard()->getWhitePassant().getVictim().x() * 100) + STARTING_X;
                    int y = ((controller->getBoard()->getWhitePassant().getVictim().y() - 1) * 100) + STARTING_Y;

                    painter.fillRect(x, y,100,100,Colors::special());

                    if(((controller->getBoard()->getWhitePassant().getVictim().x())+(controller->getBoard()->getWhitePassant().getVictim().y() + 1))%2==0){
                        painter.fillRect(x+10,y+10,80,80,Colors::light());
                    }else{
                        painter.fillRect(x+10,y+10,80,80,Colors::dark());
                    }

                } else if(attack2x==highlightedX && attack2y==highlightedY){
                    int x = (controller->getBoard()->getWhitePassant().getVictim().x() * 100) + STARTING_X;
                    int y = ((controller->getBoard()->getWhitePassant().getVictim().y() - 1) * 100) + STARTING_Y;

                    painter.fillRect(x, y,100,100,Colors::special());

                    if(((controller->getBoard()->getWhitePassant().getVictim().x())+(controller->getBoard()->getWhitePassant().getVictim().y() + 1))%2==0){
                        painter.fillRect(x+10,y+10,80,80,Colors::light());
                    }else{
                        painter.fillRect(x+10,y+10,80,80,Colors::dark());
                    }

                }
            }
        }
        /**else if(controller->getBoard()->getPiece(highlightedX,highlightedY)==6){//white knight
            if(controller->getBoard()->isWhiteLongCastle()){
                int x = 200 + STARTING_X;
                int y = 700 + STARTING_Y;

                painter.fillRect(x,y,100,100,Colors::move());
                painter.fillRect(x+10,y+10,80,80,Colors::dark());
            }
            if(controller->getBoard()->isWhiteCastle()){
                int x = 600 + STARTING_X;
                int y = 700 + STARTING_Y;

                painter.fillRect(x,y,100,100,Colors::move());
                painter.fillRect(x+10,y+10,80,80,Colors::dark());
            }
        }
        else if(controller->getBoard()->getPiece(highlightedX,highlightedY)==-6){//black knight
            if(controller->getBoard()->isBlackLongCastle()){
                int x = 200 + STARTING_X;
                int y = 000 + STARTING_Y;

                painter.fillRect(x,y,100,100,Colors::move());
                painter.fillRect(x+10,y+10,80,80,Colors::light());
            }
            if(controller->getBoard()->isBlackCastle()){
                int x = 600 + STARTING_X;
                int y = 000 + STARTING_Y;

                painter.fillRect(x,y,100,100,Colors::move());
                painter.fillRect(x+10,y+10,80,80,Colors::light());
            }
        }**/
    }


    QFont font = painter.font();
    font.setPixelSize(32);
    painter.setFont(font);

    painter.drawText(15,70,"8");
    painter.drawText(15,170,"7");
    painter.drawText(15,270,"6");
    painter.drawText(15,370,"5");
    painter.drawText(15,470,"4");
    painter.drawText(15,570,"3");
    painter.drawText(15,670,"2");
    painter.drawText(15,770,"1");

    painter.drawText(75,840,"A");
    painter.drawText(175,840,"B");
    painter.drawText(275,840,"C");
    painter.drawText(375,840,"D");
    painter.drawText(475,840,"E");
    painter.drawText(575,840,"F");
    painter.drawText(675,840,"G");
    painter.drawText(775,840,"H");
}

void Window::mousePressEvent(QMouseEvent *event) {
    if(event->x()>=STARTING_X&&event->x()<=STARTING_X+800){ //if inside the playing area x
        if(event->y()>=STARTING_Y&&event->y()<=STARTING_Y+800){//if inside the playing area y
            int x = (event->x() - STARTING_X)/100; //get x quadrant
            int y = (event->y() - STARTING_Y)/100; //get y quadrant
//            std::cout << "Mouse Pressed at quadrant:" << x << ", " << y << std::endl;

            emit sendClick(x,y);
        }
    }

//    std::cout << "Mouse Pressed at pixels:" << event->x() << ", " << event->y() << std::endl << std::endl;
}

void Window::showMessage(QString message) {
    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
