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
    double getSumWeight(int,int, int);
    void updateWeight(int);
    void updateWeightRegression();
    void initWeight();
    double randNN(double, double);
    double *getOutput();
    double getDelta(int, int, int);
    double getDeltaRegression(int, int);
    void updateOutput();
    void setInput(double*);
private:
    int nbLayers;
    double** network;
    double*** weight;
    int* sizeLayers;
    double* expeted;
    void initNetwork(double*);
};


#endif //MACHINE_LEARNING_MULTICOUCHE_H
