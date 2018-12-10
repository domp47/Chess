#ifndef NN_H
#define NN_H

#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/array_ops.h"
#include "tensorflow/cc/saved_model/loader.h"
#include "third_party/eigen3/Eigen/Core"

class NeuralNetwork {
public:
    NeuralNetwork(std::string graphPath, std::string checkpointPath);
    void print3DTensor(std::vector<std::string> flattenedTensor, int planes, int rows, int cols);
    void calculateScore(std::array<std::array<int, 8>, 8> gameBoard, int output[2]);

private:
    tensorflow::Tensor convertBoardToTensor(std::array<std::array<int, 8>, 8> gameBoard);

private:
    tensorflow::Session* sess;
};

#endif // NN_H