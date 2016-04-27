//
// Created by bidau on 26/04/2016.
//

#include <cstdlib>
#include <iostream>

using namespace std;

extern "C"{

    __declspec(dllexport) double* createModel(int nbInput){
        double * model = new double[nbInput];
        for(int i = 0; i < nbInput; i++){
            model[i] = 0;
        }
        return model;
    }

    __declspec(dllexport) double perceptron(double* value, double*  model, int size){
        double sum = 0;
        for(int i = 0; i < size; i++){
            sum+= value[i]*model[i];
        }

        return (sum<0)?-1:1;
    }

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

    __declspec(dllexport) void pal(double* exemplValue, int size,int inputSize, double* model, double* waitValue, double coef, int maxIter){
        int iter = 0;
        double** value = cleanArray(exemplValue, size, inputSize);
        while(iter < maxIter) {
            for (int i = 0; i < size/inputSize; i++) {
                if (waitValue[i] != perceptron(value[i], model, inputSize)) {
                    double xk = 1;
                    for(int j = 0; j < inputSize; j++){
                        xk = xk * value[i][j];
                    }
                    model[i] = model[i] + (coef * xk * waitValue[i]);
                }
            }
            iter++;
        }
    }

    __declspec(dllexport) double lineaire(int w[], int x[], int sumLength){
        int sum = 0;
        for(int i = 0; i < sumLength; i++){
            sum+= w[i] * x[i];
        }
        return sum;
    }

    int main(void){
        double* model = createModel(2);

        double* wait = new double[3];
        wait[0]= 1;
        wait[1]= -1;
        wait[2]= 1;

        double* pDouble = new double[6];
        pDouble[0]=6.65;
        pDouble[1]=1.49;
        pDouble[2]=1.92;
        pDouble[3]=-1.86;
        pDouble[4]=-1.92;
        pDouble[5]=0.9;

        pal(pDouble,6,2, model, wait, 0.1,25);

        cout << "model" << endl;
        for(int i = 0; i < 2; i++){
            cout << model[i] << endl;
        }
    }
}