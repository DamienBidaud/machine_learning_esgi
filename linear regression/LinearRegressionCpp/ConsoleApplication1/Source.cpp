//
//#include <cstdlib>
//#include <iostream>
//#include <Eigen/Dense>
//#include <Eigen/Eigenvalues>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

extern "C"
{
	double randValue(double max, double min) {
			return min + ((rand() / (double)RAND_MAX) * (max - min));
	}

	__declspec(dllexport) void cleanModel(double * model)
	{
		free(model);
	}

	__declspec(dllexport) double * lineaire_model(int nbInput)
	{
		double * model = (double *)malloc((nbInput + 1) * sizeof(double));
		model[0] = 1;

		for (int i = 1; i <= nbInput; ++i)
		{
			model[i] = randValue(1, -1);
		}
		return model;
	}

	__declspec(dllexport) double classifyRegression(double* model, double* input, int inputSize)
	{
		double sum = model[0];
		for (int i = 0; i < inputSize; ++i)
		{
			sum += model[i + 1] * input[i];
		}
		return sum;
	}

	__declspec(dllexport) void regression(double* model, double* valueSend, int size, int inputSize, double* waitValue)
	{
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> entry(size, inputSize + 1);
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> waited(size, 1);

		for (int i = 0; i < size; ++i)
		{
			waited(i, 0) = *waitValue;
			++waitValue;
		}

		for (int i = 0; i < size; ++i)
		{
			entry(i, 0) = 1.0;
			for (int j = 1; j < inputSize + 1; ++j)
			{
				entry(i, j) = *valueSend;
				++valueSend;
			}
		}

		Eigen::MatrixXd transposedMatrix = entry.transpose();
		Eigen::MatrixXd inverseMatrix = (transposedMatrix*entry).inverse();
		Eigen::MatrixXd final = inverseMatrix*transposedMatrix;
		Eigen::MatrixXd weight = final*waited;

		for (int i = 0; i < weight.rows(); ++i)
		{
			*model = weight(i, 0);
			++model;
		}
	}
}