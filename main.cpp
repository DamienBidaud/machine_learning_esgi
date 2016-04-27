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

    int perceptron(int value, double  model){
        int sum = 0;
        sum+= value*model;

        return sum;
    }

    double* initW(int size){
        double* W = new double[size];
        for(int i = 0; i < size; i++){
            W[i] = randome(-1, 1);
        }

        return W;
    }

    double* pal(int* exemplValue, int size, double* model, int* waitValue, double coef){
        double* W = initW(size);
        for(int i = 0; i < size; i++){

            if(waitValue[i] != perceptron(exemplValue[i], model[i])){
                W[i] = W[i]+(coef*exemplValue[i]*model[i]);
            }

        }

        return W;
    }

    double lineaire(int w[], int x[], int sumLength){
        int sum = 0;
        for(int i = 0; i < sumLength; i++){
            sum+= w[i] * x[i];
        }
        return sum;
    }

    int main(void){
        double* model = createModel(6);
        cout << "model" << endl;
        for(int i = 0; i < 6; i++){

            cout << model[i] << endl;
        }
    }
}