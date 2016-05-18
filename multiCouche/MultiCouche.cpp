//
// Created by bidau on 29/04/2016.
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "MultiCouche.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int nbLayers, double* expected, double* input, int* sizeLayer) {
    this->nbLayers = nbLayers+1;
    this->expeted = expected;
    this->sizeLayers = sizeLayer;
    initWeight();
    initNetwork(input);

}

void NeuralNetwork::initNetwork(double* input) {
    this->network = new double*[this->nbLayers];
    this->network[0] = input;
    for(int i = 1; i < this->nbLayers; i++){
        this->network[i] = new double[this->sizeLayers[i]];
        for (int q = 0; q < this->sizeLayers[i]; q++) {
            this->network[i][q] = this->getOut(i, q);
        }
    }
}

void NeuralNetwork::initWeight() {
    this->weight = new double**[this->nbLayers+1];
    for(int i = 0; i < this->nbLayers+1; i++){
        this->weight[i] = new double *[this->sizeLayers[i]];
        for (int j = 0; j < this->sizeLayers[i]; j++) {
            this->weight[i][j] = new double[this->sizeLayers[i+1]];
            for (int q = 0; q < this->sizeLayers[i+1]; q++) {
                this->weight[i][j][q] = randNN(1, -1);
            }
        }
    }
}


NeuralNetwork::~NeuralNetwork() {


    for(int i = 0; i < this->nbLayers; i++){
        delete[] this->network[i];
    }


    for(int j = 0; j < this->sizeLayers[0]; j++){
        delete [] this->weight[0][j];
    }
    delete[] this->weight[0];

    for(int i = 1; i < this->nbLayers; i++){
        for(int j = 0; j < this->sizeLayers[i]; j++){
            delete [] this->weight[i][j];
        }
        delete[] this->weight[i];
    }

}

/*void NeuralNetwork::getLastRegression() {
    for(int i = 0; i < this->nbNeurons; i++){
        this->network[this->nbLayers-1][i] = (getOut(this->nbLayers-1, i))-expeted[i];
    }
}*/

double NeuralNetwork::getOut(int layer, int neurone) {
    double weight = 0.1;
    for (int i = 1; i <  this->sizeLayers[layer]; i++) {
        if(layer-1>0) {
            weight += (this->weight[layer - 1][i][neurone] * this->network[layer - 1][i]);
        }
    }

    return tanh(weight);
}

double NeuralNetwork::getSumWeight(int layer, int position){
    double sum = 1;
    if(layer >0) {
        sum = 0;
        for (int j = 1; j <  this->sizeLayers[layer]; j++) {
            if(layer-1>0) {
                sum += (this->weight[layer - 1][position][j]) * getDelta(layer,j);
            }
        }
    }
    return sum;
}

void NeuralNetwork::updateWeight() {
    for(int i = 1; i < this->nbLayers; i++){
        for(int j = 0; j < this->sizeLayers[i]; j++){
            for(int q = 0; q < this->sizeLayers[i+1]; q++){
                this->weight[i][j][q] = this->weight[i][j][q] -  (0.1*(network[i-1][j]*getDelta(i,q)));
            }
        }
    }
}



double NeuralNetwork::randNN(double max, double min) {
    return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}




double *NeuralNetwork::getOutput() {

    double* out = this->network[this->nbLayers-1];
    return out;
}

double NeuralNetwork::getDelta(int layer, int neurone) {
    if(layer == this->nbLayers-1){
        return (1-(this->network[layer][neurone]*this->network[layer][neurone]))*(this->network[layer][neurone]-expeted[neurone]);
    }else{
        return (1- (this->network[layer-1][neurone]*this->network[layer-1][neurone]))*getSumWeight(layer, neurone);
    }
}

void NeuralNetwork::updateOutput() {
    for(int i = 0; i < this->nbLayers; i++){
        for(int j = 0; j < this->sizeLayers[i]; j++){
            this->network[i][j] = getOut(i,j);
        }
    }
}





























