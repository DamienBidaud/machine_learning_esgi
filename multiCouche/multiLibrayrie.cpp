//
// Created by bidau on 15/05/2016.
//

#include "MultiCouche.h"

extern "C"{

    __declspec(dllexport)double* train(double* input, int size, int nbNeurone, int training, double* expected, int inputSize ){
        NeuralNetwork neuralNetwork(size, nbNeurone, expected, input, inputSize);
        int i = 0;
        while(i < training) {
            neuralNetwork.getLastRegression();
            neuralNetwork.getValues();
            neuralNetwork.updateWeight();
            i++;
        }
        return neuralNetwork.getOutput();
    }
}