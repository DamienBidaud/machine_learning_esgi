//
// Created by bidau on 29/04/2016.
//

#ifndef MACHINE_LEARNING_MULTICOUCHE_H
#define MACHINE_LEARNING_MULTICOUCHE_H


class NeuralNetwork {
public:
    NeuralNetwork(int, int,int, int, double*, double*);
    void getLastValue();
    void getValues();
    double getOut(int, int);
    ~NeuralNetwork();
    double getSumWeight(int,int);
    void updateWeight();
    void initWeight();
private:
    int nbLayers;
    int nbNeurons;
    double** network;
    double lastLayer;
    double* layers;
    double* expeted;
    double*** weight;
    void initNetwork(int, int, double*);

};


#endif //MACHINE_LEARNING_MULTICOUCHE_H
