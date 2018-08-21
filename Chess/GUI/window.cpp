#include "window.h"
#include "Controller/controller.h"
#include "Board/board.h"

/**
 *  Construct GUI with refrence to the game controller
 * 
 * @param controller
 */
Window::Window(Controller* controller) {
    this->setFixedWidth(850);
    this->setFixedHeight(850);

    map = new ImageMap();

    connect(controller, SIGNAL(sendPawnPromotion(int, int)), this, SLOT(receivePawnPromotion(int, int)));
    connect(controller, SIGNAL(sendMessage(QString)), this, SLOT(showMessage(QString)));
}

/**
 * Draws the board on the canvas
 */
void Window::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(0,0,850,850,Colors::background());

    int highlightedX = highlightedCache.x();
    int highlightedY = highlightedCache.y();

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

            int piece = boardCache[y][x];

            if(piece!=0){
                std::string imgLoc = map->getItem(piece);
                QImage image(QString::fromStdString(imgLoc));
                QPoint pt(xLoc+20,yLoc+20);
                painter.drawImage(pt,image);
            }
        }
    }

    for(Move m: movesCache){
        int xLoc = (m.end.x() * 100) + STARTING_X;
        int yLoc = (m.end.y() * 100) + STARTING_Y;

        if(boardCache[m.end.y()][m.end.x()]==0)
            painter.fillRect(xLoc,yLoc,100,100,Colors::move());
        else
            painter.fillRect(xLoc,yLoc,100,100,Colors::special());

        if(m.special==1){
            int xAttack = (m.end.x() * 100) + STARTING_X;
            int yAttack = (m.init.y() * 100) + STARTING_Y;

            painter.fillRect(xAttack,yAttack,100,100,Colors::special());
        }

        yLoc +=10;
        xLoc +=10;

        if((m.end.x()+m.end.y())%2==0)
            painter.fillRect(xLoc, yLoc,80,80,Colors::light());
        else
            painter.fillRect(xLoc, yLoc,80,80,Colors::dark());

        int piece = boardCache[m.end.y()][m.end.x()];

        xLoc -= 10;
        yLoc -= 10;

        if(piece!=0){
            std::string imgLoc = map->getItem(piece);
            QImage image(QString::fromStdString(imgLoc));
            QPoint pt(xLoc+20,yLoc+20);
            painter.drawImage(pt,image);
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

/**
 *  Event triggers when there is a mouse click on the canvas
 * 
 * @param event
 */
void Window::mousePressEvent(QMouseEvent *event) {
    if(event->x()>=STARTING_X&&event->x()<=STARTING_X+800){ //if inside the playing area x
        if(event->y()>=STARTING_Y&&event->y()<=STARTING_Y+800){//if inside the playing area y
            int x = (event->x() - STARTING_X)/100; //get x quadrant
            int y = (event->y() - STARTING_Y)/100; //get y quadrant

            emit sendClick(x,y);
        }
    }
}

/**
 *  Shows a messag on the GUI thread
 * 
 * @param message message to display
 */
void Window::showMessage(QString message) {
    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}

/**
 *  Updates cache 
 *      Board,
 *      Highlighted Piece,
 *      Possible Moves
 * 
 * @param board
 * @param highlight
 * @param possibleMoves
 */
void Window::updateCache(std::array<std::array<int, 8>, 8> board, QPoint highlight, QVector<Move> possibleMoves) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            boardCache[y][x] = board[y][x];
        }
    }

    movesCache.clear();
    for (Move m: possibleMoves){
        movesCache.append(m);
    }

    highlightedCache.setX(highlight.x());
    highlightedCache.setY(highlight.y());
}

/**
 *
 *  Asks User to choose which piece to promote to
 * 
 * @param x x location of piece
 * @param y y location of piece
 */
void Window::receivePawnPromotion(int x, int y) {
    QStringList items;
    items << tr("Queen") << tr("Bishop") << tr("Knight") << tr("Rook");

    bool ok = false;
    QString item;

    while (!ok) {
        item = QInputDialog::getItem(this, tr("Pawn Promotion"), tr("Choose Upgrade: "), items, 0, false, &ok);
    }

    if(item == "Queen"){
        emit sendPawnPromotion('q', x, y);
    }else if (item == "Bishop"){
        emit sendPawnPromotion('b', x, y);
    }else if (item == "Knight"){
        emit sendPawnPromotion('k', x, y);
    }else if (item == "Rook"){
        emit sendPawnPromotion('r', x, y);
    }
}
