#include "window.h"
#include "Controller/controller.h"

Window::Window(Controller* controller) {
    this->setFixedWidth(850);
    this->setFixedHeight(850);

    this->controller = controller;
    map = new Map();

    highlightedCords[0] = -1;
    highlightedCords[1] = -1;
    possibleMoves.clear();
    lastKey = 0;

//    connect(controller->getBoard(), SIGNAL(controller->getBoard()->sendRefresh()),this,SLOT(refresh()));
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

            int piece = controller->getBoard()->getPiece(x, y);

            if(piece!=0){
                std::string imgLoc = map->getItem(piece);
                QImage image(QString::fromStdString(imgLoc));
                QPoint pt(xLoc+20,yLoc+20);
                painter.drawImage(pt,image);
            }
        }
    }

    for(QPoint p: possibleMoves){
        int xLoc = (p.x() * 100) + STARTING_X;
        int yLoc = (p.y() * 100) + STARTING_Y;

        if(controller->getBoard()->getPiece(p.x(),p.y())==0)
            painter.fillRect(xLoc,yLoc,100,100,Colors::move());
        else
            painter.fillRect(xLoc,yLoc,100,100,Colors::special());

        yLoc +=10;
        xLoc +=10;

        if((p.x()+p.y())%2==0)
            painter.fillRect(xLoc, yLoc,80,80,Colors::light());
        else
            painter.fillRect(xLoc, yLoc,80,80,Colors::dark());

        int piece = controller->getBoard()->getPiece(p.x(), p.y());

        xLoc -= 10;
        yLoc -= 10;

        if(piece!=0){
            std::string imgLoc = map->getItem(piece);
            QImage image(QString::fromStdString(imgLoc));
            QPoint pt(xLoc+20,yLoc+20);
            painter.drawImage(pt,image);
        }
    }

    if(highlightedCords[0] != -1 || highlightedCords[1] != -1){//if a piece is highlighted
        if(controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==-1){//black pawn
            if(controller->getBoard()->getBlackPassant().getPresent()){//passant possible

                //selected piece is one of the possible passant attacks
                if(controller->getBoard()->getBlackPassant().getAttacker1().x()==highlightedCords[0] && controller->getBoard()->getBlackPassant().getAttacker1().y()==highlightedCords[0]){
                    int x = (controller->getBoard()->getBlackPassant().getVictim().x() * 100 ) + STARTING_X;
                    int y = ((controller->getBoard()->getBlackPassant().getVictim().y() + 1) * 100) + STARTING_Y;

                    painter.fillRect(x, y,100,100,Colors::special());

                    if(((controller->getBoard()->getBlackPassant().getVictim().x())+(controller->getBoard()->getBlackPassant().getVictim().y() + 1))%2==0){
                        painter.fillRect(x+10,y+10,80,80,Colors::light());
                    }else{
                        painter.fillRect(x+10,y+10,80,80,Colors::dark());
                    }

                }
                if(controller->getBoard()->getBlackPassant().getAttacker2().x()==highlightedCords[0] && controller->getBoard()->getBlackPassant().getAttacker2().y()==highlightedCords[0]){
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
        else if(controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==1){//white pawn
            if(controller->getBoard()->getWhitePassant().getPresent()){//passant possible

                //selected piece is one of the possible passant attacks

                int attack1x = controller->getBoard()->getWhitePassant().getAttacker1().x();
                int attack1y = controller->getBoard()->getWhitePassant().getAttacker1().y();

                int attack2x = controller->getBoard()->getWhitePassant().getAttacker2().x();
                int attack2y = controller->getBoard()->getWhitePassant().getAttacker2().y();

                if(attack1x==highlightedCords[1] && attack1y==highlightedCords[0]){
                    int x = (controller->getBoard()->getWhitePassant().getVictim().x() * 100) + STARTING_X;
                    int y = ((controller->getBoard()->getWhitePassant().getVictim().y() - 1) * 100) + STARTING_Y;

                    painter.fillRect(x, y,100,100,Colors::special());

                    if(((controller->getBoard()->getWhitePassant().getVictim().x())+(controller->getBoard()->getWhitePassant().getVictim().y() + 1))%2==0){
                        painter.fillRect(x+10,y+10,80,80,Colors::light());
                    }else{
                        painter.fillRect(x+10,y+10,80,80,Colors::dark());
                    }

                } else if(attack2x==highlightedCords[1] && attack2y==highlightedCords[0]){
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
        else if(controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==6){//white knight
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
        else if(controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==-6){//black knight
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


    //Put all this stuff in new thread to finish gui
    int kingCords[2] = {-1,-1};
    controller->getBoard()->findKing(true,kingCords);

    int white = controller->getBoard()->checkMateStalemate(true);
    int black = controller->getBoard()->checkMateStalemate(false);

    if(white == 1){//white king check mate
        QMessageBox msg;
        msg.setText("Black Team wins");
        QPushButton *ng = msg.addButton("New Game", QMessageBox::ActionRole);
        QPushButton *end = msg.addButton("Exit", QMessageBox::NoRole);

        msg.exec();

        if(msg.clickedButton() == ng){
            controller->getBoard()->initBoard();
//            repaint();
        }else if(msg.clickedButton() == end){
            this->close();
        }
    }
    else if(black == 1){
        QMessageBox msg;
        msg.setText("White Team wins");
        QPushButton *ng = msg.addButton("New Game", QMessageBox::ActionRole);
        QPushButton *end = msg.addButton("Exit", QMessageBox::NoRole);

        msg.exec();

        if(msg.clickedButton() == ng){
            controller->getBoard()->initBoard();
//            repaint();
        }else if(msg.clickedButton() == end){
            this->close();
        }
    }else if((controller->getBoard()->getTurn()%2==0 && white==2) || (controller->getBoard()->getTurn()%2==1 && black==2)){
        QMessageBox msg;
        msg.setText("It's a Draw");
        QPushButton *ng = msg.addButton("New Game", QMessageBox::ActionRole);
        QPushButton *end = msg.addButton("Exit", QMessageBox::NoRole);

        msg.exec();

        if(msg.clickedButton() == ng){
            controller->getBoard()->initBoard();
//            repaint();
        }else if(msg.clickedButton() == end){
            this->close();
        }
    }
}

void Window::mousePressEvent(QMouseEvent *event) {
    if(event->x()>=STARTING_X&&event->x()<=STARTING_X+800){ //if inside the playing area x
        if(event->y()>=STARTING_Y&&event->y()<=STARTING_Y+800){//if inside the playing area y
            int x = (event->x() - STARTING_X)/100; //get x quadrant
            int y = (event->y() - STARTING_Y)/100; //get y quadrant
            std::cout << "Mouse Pressed at quadrant:" << x << ", " << y << std::endl;

            int prevY = highlightedCords[0]; //gets previous selected box
            int prevX = highlightedCords[1];

            if(prevY==-1 && prevX==-1){ //if nothing previously selected its on highlight piece state
                if( (controller->getBoard()->getPiece(x,y)>0 && controller->getBoard()->getTurn()%2==0) || (controller->getBoard()->getPiece(x,y)<0 && controller->getBoard()->getTurn()%2==1) ){
                    highlightedCords[0] = y;
                    highlightedCords[1] = x;
                    possibleMoves = controller->getBoard()->getMoves(x,y);
                    repaint();
                }
            }else if(prevY==y && prevX==x){ //if clicking same piece deselect piece
                highlightedCords[0] = -1;
                highlightedCords[1] = -1;
                possibleMoves.clear();
                repaint();
            }else if(isMovePossible(QPoint(x,y))){ //checks possible regular moves and moves to that piece
                //if its a pawn and moving to end of board
                if((controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==1 && y==0) || (controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==-1 && y==7)){
                    bool correctInput = false;
                    char upgrade = '0';

                    while(!correctInput){
                        QString response = QInputDialog::getText(this, "Pawn Promotion", "Enter: Q for queen, B for bishop, K for knight, R for rook.");

                        if(response == "q" || response == "Q"){
                            upgrade = 'q';
                            correctInput = true;
                        }else if(response == "b" || response == "B"){
                            upgrade = 'b';
                            correctInput = true;
                        }else if(response == "k" || response == "K"){
                            upgrade = 'k';
                            correctInput = true;
                        }else if(response == "r" || response == "R"){
                            upgrade = 'r';
                            correctInput = true;
                        }
                    }

                    controller->getBoard()->upgradePawn(highlightedCords[1],highlightedCords[0],upgrade);
                }


                controller->getBoard()->movePiece(highlightedCords[1],highlightedCords[0],x,y);
                highlightedCords[0] = -1;
                highlightedCords[1] = -1;
                possibleMoves.clear();
                repaint();

                /**if(board->checkCheck(board->getTurn() % 2 == 0)){//checks if white team is in check

                }else if(board->checkCheck(board->getTurn() % 2 == 1)){//checks if black team is in check

                }**/
            }
            else if(controller->getBoard()->getTurn()%2==0 && controller->getBoard()->getWhitePassant().getPresent()){ //if its white persons turn and there is a passant
                //check if the passant spot was clicked
                if(controller->getBoard()->getWhitePassant().getVictim().x()==x && controller->getBoard()->getWhitePassant().getVictim().y()-1==y){
                    controller->getBoard()->movePassant(highlightedCords[1],highlightedCords[0],controller->getBoard()->getWhitePassant().getVictim(), true);
                    highlightedCords[0] = -1;
                    highlightedCords[1] = -1;
                    possibleMoves.clear();
                    repaint();
                }
            }
            else if(controller->getBoard()->getTurn()%2==1 && controller->getBoard()->getBlackPassant().getPresent()){ //if its black persons turn and there is a passant
                if(controller->getBoard()->getBlackPassant().getVictim().x()==x && controller->getBoard()->getBlackPassant().getVictim().y()+1==y){
                    controller->getBoard()->movePassant(highlightedCords[1],highlightedCords[0],controller->getBoard()->getBlackPassant().getVictim(), false);
                    highlightedCords[0] = -1;
                    highlightedCords[1] = -1;
                    possibleMoves.clear();
                    repaint();
                }
            }
            //if white knight is highlighted and there is a white castle move possible
            else if(controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==6 && (controller->getBoard()->isWhiteCastle() || controller->getBoard()->isWhiteLongCastle())){
                if(controller->getBoard()->isWhiteLongCastle() && y==7 && x==2){
                    controller->getBoard()->moveCastling(1);
                    highlightedCords[0] = -1;
                    highlightedCords[1] = -1;
                    possibleMoves.clear();
                    repaint();
                }else if(controller->getBoard()->isWhiteCastle() && y==7 && x==6){
                    controller->getBoard()->moveCastling(2);
                    highlightedCords[0] = -1;
                    highlightedCords[1] = -1;
                    possibleMoves.clear();
                    repaint();
                }
            }
            //if black knight is highlighted and there is a black castle move possible
            else if(controller->getBoard()->getPiece(highlightedCords[1],highlightedCords[0])==-6 && (controller->getBoard()->isBlackCastle() || controller->getBoard()->isBlackLongCastle())){
                if(controller->getBoard()->isBlackLongCastle() && y==0 && x==2){
                    controller->getBoard()->moveCastling(3);
                    highlightedCords[0] = -1;
                    highlightedCords[1] = -1;
                    possibleMoves.clear();
                    repaint();
                }else if(controller->getBoard()->isBlackCastle() && y==0 && x==6){
                    controller->getBoard()->moveCastling(4);
                    highlightedCords[0] = -1;
                    highlightedCords[1] = -1;
                    possibleMoves.clear();
                    repaint();
                }
            }
            //if it's another of the same piece highlight that one instead
            else if( (controller->getBoard()->getPiece(x,y)>0 && controller->getBoard()->getTurn()%2==0) || (controller->getBoard()->getPiece(x,y)<0 && controller->getBoard()->getTurn()%2==1) ){
                highlightedCords[0] = y;
                highlightedCords[1] = x;
                possibleMoves = controller->getBoard()->getMoves(x,y);
                repaint();
            }
        }
    }

//    std::cout << "Mouse Pressed at pixels:" << event->x() << ", " << event->y() << std::endl << std::endl;
}

void Window::keyPressEvent(QKeyEvent *event) {
//    std::cout << "Key pressed: " <<  event->key() << std::endl;

    if(lastKey == Qt::Key_Control && event->key() == Qt::Key_N){
        controller->getBoard()->initBoard();
        repaint();
    }
    lastKey = event->key();
}

bool Window::isMovePossible(QPoint p) {
    for(QPoint point: possibleMoves){
        if(point.x()==p.x() && point.y()==p.y())
            return true;
    }
    return false;
}

void Window::redraw() {
    repaint();
}
