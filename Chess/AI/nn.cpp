#include "nn.h"

NeuralNetwork::NeuralNetwork(std::string graphPath, std::string checkpointPath){
    tensorflow::Status status = tensorflow::NewSession(tensorflow::SessionOptions(), &this->sess);
    if(! status.ok()) {
        throw std::runtime_error("Error starting Session: "+status.ToString());
    }

    tensorflow::MetaGraphDef graphDef;
    status = tensorflow::ReadBinaryProto(tensorflow::Env::Default(), graphPath, &graphDef);
    if(!status.ok()){
        throw std::runtime_error("Error Reading Graph: "+status.ToString());
    }

    status = this->sess->Create(graphDef.graph_def());
    if(!status.ok()){
        throw std::runtime_error("Error Creating Graph: "+status.ToString());
    }

    tensorflow::Tensor checkpointPathTensor(tensorflow::DT_STRING, tensorflow::TensorShape());
    checkpointPathTensor.scalar<std::string>()() = checkpointPath;
    status = this->sess->Run(
            {{ graphDef.saver_def().filename_tensor_name(), checkpointPathTensor },},
            {},
            {graphDef.saver_def().restore_op_name()},
            nullptr);
    if (!status.ok()) {
        throw std::runtime_error("Error loading checkpoint from " + checkpointPath + ": " + status.ToString());
    }
}

tensorflow::Tensor NeuralNetwork::convertBoardToTensor(std::array<std::array<int, 8>, 8> gameBoard){
    tensorflow::Tensor inputTensor(tensorflow::DT_FLOAT, tensorflow::TensorShape({9, 8, 8}));

    auto tensorMapper = inputTensor.tensor<float, 3>();

    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){ 
            int piece = gameBoard[y][x];

            bool whitePiece = piece >= 0;

            if(!whitePiece){
                piece *= -1;
            }

            if(piece == 0){
                tensorMapper(6, y, x) = 1;
            }else{
                int pLoc = piece - 1;
                tensorMapper(pLoc, y, x) = 1;

                if(whitePiece){
                    tensorMapper(7, y, x) = 1;
                }else{
                    tensorMapper(8, y, x) = 1;
                }
            }
        }
    }

    tensorflow::Tensor flatInput(tensorflow::DT_FLOAT, tensorflow::TensorShape({1, 576}));

    if(!flatInput.CopyFrom(inputTensor, tensorflow::TensorShape({1, 576}))) {
        throw std::runtime_error("Error Flatenning Tensor");
    }

    return flatInput;
}

void NeuralNetwork::print3DTensor(std::vector<std::string> flattenedTensor, int planes, int rows, int cols){
    int pos = 0;
    
    for(int p = 0; p < planes; p++){

        if(p == 0){
            std::cout << "[";
        }

        for(int r = 0; r < rows; r++){
            if(r == 0 && p != 0){
                std::cout << " [";
            }else if(r == 0){
                std::cout << "[";
            }
         
            for(int c = 0; c < cols; c++) {
                if( c== 0 && r != 0){
                    std::cout << "  [";
                }else if(c == 0){
                    std::cout << "[";
                }

                if(pos >= flattenedTensor.size()) {
                    std::cerr << "Tensor Size mismatch" << std::endl;
                    exit(1);
                }

                std::cout << flattenedTensor[pos] << " ";
                pos++;

                if(c == cols-1){
                    std::cout << "]";
                }
            }

            if(r == rows-1){
                std::cout << "]";
            }
            if(!(p == planes-1 && r == rows-1)){
                std::cout << std::endl;
            }
        }
        if(p == planes-1){
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

void NeuralNetwork::calculateScore(std::array<std::array<int, 8>, 8> gameBoard, int output[2]){
    std::vector<tensorflow::Tensor> outputs;

    tensorflow::Status status = this->sess->Run({{"Input", convertBoardToTensor(gameBoard)}}, {"Output"}, {}, &outputs);
    if(!status.ok()) {
        throw std::runtime_error("Error running session: " + status.ToString());
    }

    if(outputs.empty()){
        throw std::runtime_error("Error Getting Network Result");
    }


}