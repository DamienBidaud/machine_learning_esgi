//
// Created by bidau on 29/04/2016.
//

#include <cstdlib>
#include <cmath>
#include "MultiCouche.h"

NeuralNetwork::NeuralNetwork(int nbLayers, int nbNeurons, double* weight,int size, int inputSize, double* expected,
                             double* values) {
    this->nbLayers = nbLayers;
    this->nbNeurons = nbNeurons;
    this->weight = weight;
    this->expeted = expected;
    initNetwork(size, inputSize, values);
    this->layers = new double[this->nbLayers-1];
}

void NeuralNetwork::initNetwork(int size, int inputSize, double* values) {
    this->network = new double**[this->nbLayers];
    for(int i = 0; i < this->nbLayers; i++){
        this->network[i] = new double*[this->nbNeurons];
        for(int j = 0 ; j< this->nbNeurons; j++){
            this->network[i][j] = new double[2];
        }
    }


}

NeuralNetwork::~NeuralNetwork() {
    for(int i = 0; i < this->nbLayers; i++){
        delete[] this->network[i];
    }
    delete this->network;
    delete this->layers;
}


void NeuralNetwork::getLastValue() {
    for(int i = 0; i < this->nbNeurons; i++){
        this->network[this->nbLayers][i][0] = (1*(this->getOut(this->nbLayers, i)*this->getOut(this->nbLayers, i)))*(this->getOut(this->nbLayers,i)-expeted[i]);
    }
}

double NeuralNetwork::getOut(int layer, int neurone) {
    double weight = 0;
    for (int i = 0; i < this->nbNeurons; i++) {
        if(layer-1>=0) {
            weight += (this->network[layer - 1][i][1]) *
                      this->getOut(layer - 1, i);
        }
    }

    return tanh(weight);
}

void NeuralNetwork::getValues() {
    int position = this->nbLayers;
    for(int i = this->nbLayers-1; i > 0; i--){
        for(int j = 0; j < this->nbNeurons; j++){
            this->network[i][j][0] = (1- (this->getOut(i, j)*this->getOut(i, j)))*getSumWeight(position, j);
        }
    }
}

double NeuralNetwork::getSumWeight(int layer, int position){
    double sum = 0;
    for(int j = 1; j < this->nbNeurons; j++){
        sum += (this->network[layer-1][position][1])*this->network[layer][j][0];
    }
    return sum;
}

void NeuralNetwork::updateWeight() {

}


double randValue(double max, double min) {
    return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}













