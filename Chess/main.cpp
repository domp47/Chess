#include "Controller/chess.h"
#include <QtWidgets/QApplication>
#include <thread>
#include <string>

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    int searchDepth;

    if(argc != 2){
        std::cout << "You have not entered an Alpha Beta search depth. Using default value of 6." << std::endl;
        searchDepth = 6;
    }else{
        try{
            searchDepth = std::stoi(argv[1]);
        }catch (const std::invalid_argument &ia){
            std::cerr << argv[1] << " is not a valid search depth." << std::endl;
            exit(1);
        }
        if( searchDepth <= 0) {
            std::cerr << argv[1] << " is not a valid search depth." << std::endl;
            exit(1);
        }
    }

    const std::string graphPath = "/home/dom/projects/Chess/Model/chess.meta";
    const std::string checkpointPath = "/home/dom/projects/Chess/Model/chess";

    Chess chess(searchDepth, graphPath, checkpointPath);
    chess.playChess();

    return app.exec();
}