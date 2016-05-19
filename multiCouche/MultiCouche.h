//
// Created by bidau on 29/04/2016.
//

#ifndef MACHINE_LEARNING_MULTICOUCHE_H
#define MACHINE_LEARNING_MULTICOUCHE_H


class NeuralNetwork {
public:
    NeuralNetwork(int, double*, double*,  int*);
    double getOut(int, int);
    ~NeuralNetwork();
    double getSumWeight(int,int);
    void updateWeight();
    void updateWeightRegression();
    void initWeight();
    double randNN(double, double);
    double *getOutput();
    double getDelta(int, int);
    double getDeltaRegression(int, int);
    void updateOutput();
private:
    int nbLayers;
    double** network;
    double*** weight;
    int* sizeLayers;
    double* expeted;
    void initNetwork(double*);
};


#endif //MACHINE_LEARNING_MULTICOUCHE_H
