//
// Created by bidau on 26/04/2016.
//


extern "C"{

    /**
     * créer le model
     *//*
    __declspec(dllexport) void createModel(int nbInput, double* model){
        for(int i = 0; i < nbInput; i++){
            model[i] = 0;
        }
    }

    *//**
     * calcule le parceptron
     * val = couple de coordonée sur unity
     * model = c'est le model créer précedement
     * size = taille de l'élément
     *//*
    __declspec(dllexport) double perceptron(double* value, double*  model, int size){
        double sum = 0;
        for(int i = 0; i < size; i++){
            sum+= value[i]*model[i];
        }

        return (sum<0)?-1:1;
    }


    *//**
     * prend un tableau 1 dimension et le transform en 2 dimension
     *//*
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

   *//* __declspec(dllexport) void deleteArray(double** array, int size){
        for(int i = 0; i < size; i++){
            delete array[i];
        }
        delete array;
    }*//*

    *//**
     * entraine le model
     *//*
    __declspec(dllexport) void pal(double* exemplValue, int size,int inputSize, double* model, double* waitValue, double coef, int maxIter){
        int iter = 0;
        double** value = cleanArray(exemplValue, size, inputSize);
        while(iter < maxIter) {
            for (int i = 0; i < size/inputSize; i++) {
                if (waitValue[i] != perceptron(value[i], model, inputSize)) {
                    for(int j = 0; j < inputSize; j++){
                        model[j] = model[j] + (coef * value[i][j] * waitValue[i]);
                    }
                }
            }
            iter++;
        }
        //deleteArray(value, size/inputSize);
    }

    __declspec(dllexport) void regresion(double* valueSend, int size, int inputSize, double* waitValue, double* model){
        double** value = cleanArray(valueSend, size, inputSize);

        //Matrix3f matrix3f;

        //deleteArray(value, size/inputSize);
    }

    __declspec(dllexport) double lineaire_model(int w[], int x[], int sumLength){
        int sum = 0;
        for(int i = 0; i < sumLength; i++){
            sum+= w[i] * x[i];
        }
        return sum;
    }

*/

    __declspec(dllexport) double test(){
        return 42.0;
    }
}