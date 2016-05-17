//
// Created by bidau on 29/04/2016.
//

#ifndef MACHINE_LEARNING_MULTICOUCHE_H
#define MACHINE_LEARNING_MULTICOUCHE_H


class NeuralNetwork {
public:
    NeuralNetwork(int, int, double*, double*, int);
    void getLastValue();
    void getValues();
    double getOut(int, int);
    ~NeuralNetwork();
    double getSumWeight(int,int);
    void updateWeight();
    void initWeight();
    double randValue(double, double);
    void getLastRegression();
    double *getOutput();
private:
    int nbLayers;
    int nbNeurons;
    int sizeInput;
    double** network;
    double lastLayer;
    double* layers;
    double* expeted;
    double*** weight;
    void initNetwork(double*);
    double getSigne(int , int, int);

};


#endif //MACHINE_LEARNING_MULTICOUCHE_H
