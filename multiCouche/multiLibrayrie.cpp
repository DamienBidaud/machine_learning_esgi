//
// Created by bidau on 15/05/2016.
//

#include "MultiCouche.h"

extern "C"{

    __declspec(dllexport)double* train(int size, int nbNeurone, int training, double* expected ){
        NeuralNetwork neuralNetwork(size, nbNeurone, expected);
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