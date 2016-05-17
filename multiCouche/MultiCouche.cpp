//
// Created by bidau on 29/04/2016.
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "MultiCouche.h"

using namespace std;

NeuralNetwork::NeuralNetwork(int nbLayers, int nbNeurons, double* expected, double* input, int sizeInput) {
    this->nbLayers = nbLayers;
    this->nbNeurons = nbNeurons;
    this->expeted = expected;
    this->sizeInput = sizeInput;
    this->input = input;
    initNetwork(input);
    initWeight();
    this->layers = new double[this->nbLayers-1];
}

void NeuralNetwork::initNetwork(double* input) {
    this->network = new double*[this->nbLayers];
    for(int i = 0; i < this->nbLayers; i++){

        this->network[i] = new double[this->nbNeurons];
        for (int q = 0; q < this->nbNeurons; q++) {
            this->network[i][q] = randValue(1, -1);
        }
    }
}

void NeuralNetwork::initWeight() {
    this->weight = new double**[this->nbLayers+1];
    for(int i = 0; i < this->nbLayers+1; i++){
        if(i==0){
            this->weight[i] = new double *[this->nbNeurons];
            for (int j = 0; j < this->sizeInput; j++) {
                this->weight[i][j] = new double[this->nbNeurons];
                for (int q = 0; q < this->nbNeurons; q++) {
                    this->weight[i][j][q] = randValue(1, -1);
                }
            }
        }else {
            this->weight[i] = new double *[this->nbNeurons];
            for (int j = 0; j < this->nbNeurons; j++) {
                this->weight[i][j] = new double[this->nbNeurons];
                for (int q = 0; q < this->nbNeurons; q++) {
                    this->weight[i][j][q] = randValue(1, -1);
                }
            }
        }
    }
}


NeuralNetwork::~NeuralNetwork() {
    for(int i = 0; i < this->nbLayers+1; i++){
        delete[] this->network[i];
    }

    for(int j = 0; j < this->sizeInput; j++){
        delete [] this->weight[0][j];
    }
    delete[] this->weight[0];

    for(int i = 1; i < this->nbLayers+1; i++){
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
        this->network[this->nbLayers][i] = ((this->getOut(this->nbLayers, i)*this->getOut(this->nbLayers, i)))*(this->getOut(this->nbLayers,i)-expeted[i]);
    }
}

double NeuralNetwork::getOut(int layer, int neurone) {
    double weight = 0;
    /*for (int i = 0; i < this->sizeInput; i++) {
        if(layer-1>=0) {
            weight += (this->weight[layer - 1][i][neurone]) *
                      this->getOut(layer - 1, i);
            cout << weight<< endl;
        }
    }*/
    for (int i = 1; i < this->nbNeurons; i++) {
        if(layer-1>0) {
            weight += (this->weight[layer - 1][i][neurone] * this->network[layer - 1][i]);
        }
    }

    return tanh(weight);
}

void NeuralNetwork::getValues() {
    int position = this->nbLayers-1;
    for(int i = this->nbLayers-2; i > 0; i--){
        for(int j = 0; j < this->nbNeurons; j++){
            this->network[i][j] = (1- (this->getOut(i, j)*this->getOut(i, j)))*getSumWeight(position, j);
        }
        position--;
    }

}

double NeuralNetwork::getSumWeight(int layer, int position){
    double sum = 0;

    if(layer >0) {
        for (int j = 1; j < this->nbNeurons; j++) {
            sum += (this->weight[layer - 1][position][j]) * this->network[layer][j];
        }
    }
    return sum;
}

void NeuralNetwork::updateWeight() {
    for(int j = 0; j < this->sizeInput; j++){
        for(int q = 0; q < this->nbNeurons; q++){
            this->weight[0][j][q] = this->weight[0][j][q] - this->getSigne(0, j, q);
        }
    }

    for(int i = 1; i < this->nbLayers-1; i++){

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

void NeuralNetwork::getLastRegression() {
    for(int i = 0; i < this->nbNeurons; i++){
        this->network[this->nbLayers-1][i] = (getOut(this->nbLayers-1, i))-expeted[i];
    }
}

double *NeuralNetwork::getOutput() {
    double* out = this->network[this->nbLayers-1];
    cout << "ok"<<endl;
    return out;
}



















