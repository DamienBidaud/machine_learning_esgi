//
// Created by bidau on 29/04/2016.
//

#include <cstdlib>
#include <cmath>
#include "MultiCouche.h"

NeuralNetwork::NeuralNetwork(int nbLayers, int nbNeurons,int size, int inputSize, double* expected,
                             double* values) {
    this->nbLayers = nbLayers;
    this->nbNeurons = nbNeurons;
    this->expeted = expected;
    initNetwork();
    initWeight();
    this->layers = new double[this->nbLayers-1];
}

void NeuralNetwork::initNetwork() {
    this->network = new double*[this->nbLayers];
    for(int i = 0; i < this->nbLayers; i++){
        this->network[i] = new double[this->nbNeurons];

    }
}

void NeuralNetwork::initWeight() {
    this->weight = new double**[this->nbLayers];
    for(int i = 0; i < this->nbLayers; i++){
        this->weight[i] = new double*[this->nbNeurons];
        for(int j = 0 ; j < this->nbNeurons; j++){
            this->weight[i][j] = new double[this->nbNeurons];
            for(int q = 0 ; q < this->nbNeurons; q++){
                this->weight[i][j][q] = randValue(1, -1);
            }
        }
    }
}


NeuralNetwork::~NeuralNetwork() {
    for(int i = 0; i < this->nbLayers; i++){
        delete[] this->network[i];
    }
    for(int i = 0; i < this->nbLayers; i++){
        for(int j = 0; j < this->nbNeurons; j++){
            delete [] this->weight[i][j];
        }
        delete[] this->weight[i];
    }

    delete this->network;
    delete this->weight;
    delete this->layers;
}


void NeuralNetwork::getLastValue() {
    for(int i = 0; i < this->nbNeurons; i++){
        this->network[this->nbLayers][i] = (1*(this->getOut(this->nbLayers, i)*this->getOut(this->nbLayers, i)))*(this->getOut(this->nbLayers,i)-expeted[i]);
    }
}

double NeuralNetwork::getOut(int layer, int neurone) {
    double weight = 0;
    for (int i = 0; i < this->nbNeurons; i++) {
        if(layer-1>=0) {
            weight += (this->weight[layer - 1][i][neurone]) *
                      this->getOut(layer - 1, i);
        }
    }

    return tanh(weight);
}

void NeuralNetwork::getValues() {
    int position = this->nbLayers;
    for(int i = this->nbLayers-1; i > 0; i--){
        for(int j = 0; j < this->nbNeurons; j++){
            this->network[i][j] = (1- (this->getOut(i, j)*this->getOut(i, j)))*getSumWeight(position, j);
        }
    }
}

double NeuralNetwork::getSumWeight(int layer, int position){
    double sum = 0;
    for(int j = 1; j < this->nbNeurons; j++){
        sum += (this->weight[layer-1][position][j])*this->network[layer][j];
    }
    return sum;
}

void NeuralNetwork::updateWeight() {
    for(int i = 0; i < this->nbLayers; i++){
        for(int j = 0; j < this->nbNeurons; j++){
            for(int q = 0; q < this->nbNeurons; q++){
                this->weight[i][j][q] = this->weight[i][j][q] - this->getSigne(i, j, q);
            }
        }
    }
}



double NeuralNetwork::randValue(double max, double min) {
    return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}

double NeuralNetwork::getSigne(int layer, int i, int j) {
    return ((getOut(layer-1, i)*network[layer][j])>0)?1:-1;
}















