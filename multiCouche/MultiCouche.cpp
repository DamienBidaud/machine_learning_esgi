//
// Created by bidau on 29/04/2016.
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "MultiCouche.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int nbLayers, int nbNeurons, double* expected, double* input, int sizeInput) {
    this->nbLayers = nbLayers+1;
    this->nbNeurons = nbNeurons;
    this->expeted = expected;
    this->sizeInput = sizeInput;
    initWeight();
    initNetwork(input);
    this->layers = new double[this->nbLayers-1];
}

void NeuralNetwork::initNetwork(double* input) {
    this->network = new double*[this->nbLayers];
    this->network[0] = input;
    for(int i = 1; i < this->nbLayers; i++){
        this->network[i] = new double[this->nbNeurons];
        for (int q = 0; q < this->nbNeurons; q++) {
            this->network[i][q] = this->getOut(i, q);
        }
    }
}

void NeuralNetwork::initWeight() {
    this->weight = new double**[this->nbLayers];
    for(int i = 0; i < this->nbLayers; i++){
        this->weight[i] = new double *[this->nbNeurons];
        for (int j = 0; j < this->nbNeurons; j++) {
            this->weight[i][j] = new double[this->nbNeurons];
            for (int q = 1; q < this->nbNeurons; q++) {
                this->weight[i][j][q] = randNN(1, -1);
            }
        }
    }
}


NeuralNetwork::~NeuralNetwork() {


    for(int i = 0; i < this->nbLayers; i++){
        delete[] this->network[i];
    }


    for(int j = 0; j < this->sizeInput; j++){
        delete [] this->weight[0][j];
    }
    delete[] this->weight[0];

    for(int i = 1; i < this->nbLayers; i++){
        for(int j = 0; j < this->nbNeurons; j++){
            delete [] this->weight[i][j];
        }
        delete[] this->weight[i];
    }

//    delete this->network;
//
//    delete this->weight;
//
//    delete this->layers;
//
//    delete this->expeted;


}


void NeuralNetwork::getLastValue() {
    for(int i = 0; i < this->nbNeurons; i++){
        this->network[this->nbLayers-1][i] = ((this->getOut(this->nbLayers-1, i)*this->getOut(this->nbLayers-1, i)))*(this->getOut(this->nbLayers-1,i)-expeted[i]);
    }
}

void NeuralNetwork::getLastRegression() {
    for(int i = 0; i < this->nbNeurons; i++){
        this->network[this->nbLayers-1][i] = (getOut(this->nbLayers-1, i))-expeted[i];
    }
}

double NeuralNetwork::getOut(int layer, int neurone) {
    double weight = 0.1;
    for (int i = 1; i < this->nbNeurons; i++) {
        if(layer-1>0) {
            weight += (this->weight[layer - 1][i][neurone] * this->network[layer - 1][i]);
        }
    }

    return tanh(weight);
}

void NeuralNetwork::getValues() {

    int position = this->nbLayers-2;
    for(int i = this->nbLayers-3; i > 0; i--){
        for(int j = 0; j < this->nbNeurons; j++){
            this->network[i][j] = (1- (this->getOut(i-1, j)*this->getOut(i-1, j)))*getSumWeight(position, j);
        }
        position--;
    }

}

double NeuralNetwork::getSumWeight(int layer, int position){
    double sum = 1;
    if(layer >0) {
        sum = 0;
        for (int j = 1; j < this->nbNeurons; j++) {
            if(layer-1>0) {
                sum += (this->weight[layer - 1][position][j]) * this->network[layer][j];
            }
        }
    }
    return sum;
}

void NeuralNetwork::updateWeight() {
    for(int j = 0; j < this->sizeInput; j++){
        for(int q = 0; q < this->nbNeurons; q++){
            this->weight[0][j][q] = this->weight[0][j][q] - (0.1*(getOut(0, j)*network[0][j]));
        }
    }

    for(int i = 1; i < this->nbLayers-1; i++){
        for(int j = 0; j < this->nbNeurons; j++){
            for(int q = 0; q < this->nbNeurons; q++){
                this->weight[i][j][q] = this->weight[i][j][q] -  (0.1*(getOut(i-1, j)*network[i][q]));
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



















