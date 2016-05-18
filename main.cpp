//
// Created by bidau on 26/04/2016.
//

#include <cstdlib>
#include <iostream>
#include "multiCouche/MultiCouche.h"

using namespace std;

extern "C"{


    double randValue(double max, double min) {
        return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
    }

    int randPos(int max, int min){
        return (max - min) * (rand() / RAND_MAX) + min;
    }
    /**
     * créer le model
     */
    __declspec(dllexport) void createModel(int nbInput, double* model){
        for(int i = 0; i < nbInput; i++){
            model[i] = randValue(-1,1);
        }
    }

    /**
     * calcule le parceptron
     * val = couple de coordonée sur unity
     * model = c'est le model créer précedement
     * size = taille de l'élément
     */
    __declspec(dllexport) double perceptron(double* value, double*  model, int size){
        double sum = 0;
        for(int i = 0; i < size; i++){
            sum+= value[i]*model[i];
        }

        return (sum<0)?-1:1;
    }


    /**
     * prend un tableau 1 dimension et le transform en 2 dimension
     */
     double** cleanArray(double* value, int size, int sizeElement){
        double** array = new double*[size/sizeElement];
        for(int i = 0; i < size/sizeElement; i++){
            array[i] = new double[sizeElement];
        }
        int pos = 0;
        int i = 0;
        while(i < size){
            for(int j = 0; j < sizeElement; j++){
                array[pos][j] = value[i+j];
            }
            i = i + sizeElement;
            pos++;
        }
        return array;
    }

    void deleteArray(double** array, int size){
        for(int i = 0; i < size; i++){
            delete[] array[i];
        }
        delete array;
    }

    /**
     * entraine le model
     */
    __declspec(dllexport) void pal(double* exemplValue, int size,int inputSize, double* model, double* waitValue, double coef, int maxIter){
        int iter = 0;
        double** value = cleanArray(exemplValue, size, inputSize);
        int i = 0;
        while(iter < maxIter) {
            /*for (int i = 0; i < size/inputSize; i++) {
                if (waitValue[i] != perceptron(value[i], model, inputSize)) {
                    for(int j = 0; j < inputSize; j++){
                        model[j] = model[j] + (coef * (waitValue[i] *value[i][j]));
                    }
                }
            }*/
            i = randPos(size/inputSize, 0);
            if (waitValue[i] != perceptron(value[i], model, inputSize)) {
                for(int j = 0; j < inputSize; j++){
                    model[j] = model[j] + (coef * (waitValue[i] *value[i][j]));
                }
            }
            iter++;
        }
        deleteArray(value, size/inputSize);
    }



    __declspec(dllexport) void regresion(double* valueSend, int size, int inputSize, double* waitValue, double* model){
        double** value = cleanArray(valueSend, size, inputSize);
    }

    __declspec(dllexport)double* train(double* input, int size, int training, double* expected, int* sizeLayers ){
        NeuralNetwork neuralNetwork(size, expected, input, sizeLayers);
        int i = 0;
        while(i < training) {

            neuralNetwork.updateWeight();
            neuralNetwork.updateOutput();
            i++;
        }
        return neuralNetwork.getOutput();

    }

    __declspec(dllexport)double* trainRegression(double* input, int size, int nbNeurone, int training, double* expected, int inputSize,int* sizeLayer ){
        //NeuralNetwork neuralNetwork(size, nbNeurone, expected, input, inputSize, sizeLayer);
        int i = 0;
        while(i < training) {
            //neuralNetwork.getLastRegression();
        //    neuralNetwork.updateWeight();
            i++;
        }
        //double* out = neuralNetwork.getOutput();
        return 0;
    }


    int main(void){
        cout << "start" << endl;
        double* input = new double[6];
        input[0]= 0;
        input[1]= 0;
        input[2]= 0;
        input[3]= 1;
        input[4]= 1;
        input[5]= 1;
        double* expected = new double[4];
        expected[0]=1;
        expected[1]=1;
        expected[2]=-1;

        int* sizeLayer = new int[3];
        sizeLayer[0] = 6;
        sizeLayer[1] = 1;
        sizeLayer[2] = 1;
        cout << "---------------------------classification------------------------" << endl;
        double * test = train(input, 3, 1000, expected, sizeLayer);
        for(int i = 0; i < sizeLayer[2]; i++){
            cout <<test[i]<<endl;
        }

       /* cout << "---------------------------regression------------------------" << endl;


        test = trainRegression(input, 2, 8, 10, expected, 4);
        for(int i = 0; i < 8; i++){
            cout <<test[i]<<endl;
        }*/

        cout << "end" << endl;
    }

}