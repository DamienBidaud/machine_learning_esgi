//
// Created by bidau on 26/04/2016.
//

#include <cstdlib>
#include <iostream>

using namespace std;

extern "C"{

    double randome(int min, int max){
        return rand() % (max - min + 1) + min;
    }


    double* createModel(int nbInput){
        double * model = new double[nbInput];
        for(int i = 0; i < nbInput; i++){
            model[i] = 0;
        }
        return model;
    }

    double perceptron(double* value, double*  model, int size){
        double sum = 0;
        for(int i = 0; i < size; i++){
            sum+= value[i]*model[i];
        }

        return (sum<0)?-1:1;
    }

    double* initW(int size){
        double* W = new double[size];
        for(int i = 0; i < size; i++){
            W[i] = randome(-1, 1);
        }

        return W;
    }


    double** cleanArray(double* value, int size, int sizeElement){
        double** array = new double*[size/sizeElement];
        for(int i = 0; i < size/sizeElement; i++){
            array[i] = new double[sizeElement];
        }
        return array;
    }

    void pal(double* exemplValue, int size,int inputSize, double* model, double* waitValue, double coef, int maxIter){
        int iter = 0;
        double** value = cleanArray(exemplValue, size, inputSize);
        while(iter < maxIter) {
            for (int i = 0; i < size/inputSize; i++) {
                if (waitValue[i] != perceptron(value[i], model, inputSize)) {
                    model[i] = model[i] + (coef * exemplValue[i] * waitValue[i]);
                }
            }
            iter++;
        }
    }

    double lineaire(int w[], int x[], int sumLength){
        int sum = 0;
        for(int i = 0; i < sumLength; i++){
            sum+= w[i] * x[i];
        }
        return sum;
    }

    int main(void){
        double* model = createModel(2);
        double* wait = new double[6];
        wait[0]= 1;
        wait[1]= -1;
        wait[2]= 1;
        wait[3]= 1;
        wait[4]= -1;
        wait[5]= 1;
        cout << "model" << endl;
        for(int i = 0; i < 2; i++){

            cout << model[i] << endl;
        }
    }
}