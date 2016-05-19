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
        return rand()%(max-min + 1) + min;;
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

    double* selectTrain(double* input, int pos, int size){
        double *val = new double[size];
        int i = 0;
        int q = 0;
        while(i < pos){
            for(int j = 0; j <= size; j++){
                val[j] = input[q];
                q++;
            }
            i++;
        }
        return val;
    };

    __declspec(dllexport)NeuralNetwork train(double* input, int size, int training, double* expected, int* sizeLayers, int nbExemple ){
        NeuralNetwork neuralNetwork(size, expected, input, sizeLayers);
        int i = 0;
        int rand = 0;
        while(i < training) {
            rand = randPos(nbExemple, 0);
            neuralNetwork.setInput(selectTrain(input, rand, sizeLayers[0]));
            neuralNetwork.updateOutput();
            if(neuralNetwork.getOutput()[sizeLayers[size-1]-1]!=expected[rand]) {
                neuralNetwork.updateWeight(rand);
            }

            i++;
        }

        return neuralNetwork;

    }

    __declspec(dllexport)double* trainRegression(double* input, int size, int training, double* expected, int* sizeLayers ){
        NeuralNetwork neuralNetwork(size, expected, input, sizeLayers);
        int i = 0;
        while(i < training) {
            neuralNetwork.updateWeightRegression();
            neuralNetwork.updateOutput();
            i++;

        }
        cout << "ok"<<endl;
        return neuralNetwork.getOutput();
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
        sizeLayer[0] = 2;
        //sizeLayer[1] = 2;
        sizeLayer[1] = 1;
        sizeLayer[2] = 1;
        cout << "---------------------------classification------------------------" << endl;
        NeuralNetwork test = train(input, 3, 1000, expected, sizeLayer, 2);
        double* value  = new double[2];
        value[0]= 0;
        value[1] = 1;

        test.setInput(value);
        test.updateOutput();
        double* output = test.getOutput();
        cout << output[0] << endl;

        cout << "---------------------------regression------------------------" << endl;


        /*test = trainRegression(input, 3, 1000, expected, sizeLayer);
        for(int i = 0; i < 8; i++){
            cout <<test[i]<<endl;
        }*/

        cout << "end" << endl;
    }

}