#include <iostream>
#include "window.h"
#include "colors.h"

Window::Window(Board* board) {
    this->setFixedWidth(850);
    this->setFixedHeight(850);

    this->board = board;
    map = new Map();

    highlightedCords[0] = -1;
    highlightedCords[1] = -1;

}

void Window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0,0,850,850,Colors::background());

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            int xLoc = (x * 100) + STARTING_X;
            int yLoc = (y * 100) + STARTING_Y;
            int size = 100;
            bool highlighted = false;

            if(y==highlightedCords[0]&&x==highlightedCords[1]){
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

            int piece = board->getPiece(x, y);

            if(piece!=0){
                std::string imgLoc = map->getItem(piece);
                QImage image(QString::fromStdString(imgLoc));
                QPoint pt(xLoc+20,yLoc+20);
                painter.drawImage(pt,image);
            }
        }
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
    if(event->x()>=STARTING_X&&event->x()<=STARTING_X+800){
        if(event->y()>=STARTING_Y&&event->y()<=STARTING_Y+800){
            int prevY = highlightedCords[0];
            int prevX = highlightedCords[1];

            int x = (event->x() - STARTING_X)/100;
            int y = (event->y() - STARTING_Y)/100;
            std::cout << "Mouse Pressed at quadrant:" << x << ", " << y << std::endl;

            if(y!=prevY||x!=prevX){
                highlightedCords[0] = y;
                highlightedCords[1] = x;
            }else{
                highlightedCords[0] = -1;
                highlightedCords[1] = -1;
            }

            repaint();
        }
    }
    std::cout << "Mouse Pressed at pixels:" << event->x() << ", " << event->y() << std::endl << std::endl;
}
