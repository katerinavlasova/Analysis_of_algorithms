#include <iostream>
#include <string>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>

using namespace std;

class Matrix
{
private:
	int rows;
	int columns;
	int** data;
public:
	Matrix(const int row, const int columns, const int** elements);
	void show_mtrx();
	friend int** classic_mult(Matrix& matr1, Matrix& matr2);
	friend int** winograd(Matrix& matr1, Matrix& matr2, int** data);
	friend int** parall_winograd(Matrix& matr1, Matrix& matr2, int** data, int NThreads);
	friend void paral(Matrix& matr1, Matrix& matr2, int** data, int* mulh, int* mulv, int num, int NThread);
};

void Matrix::show_mtrx()
{
	for (int i = 0; i < rows; i++)
	{
		printf("\n");
		for (int j = 0; j < columns; j++)
			printf("%d ", data[i][j]);
	}
}

Matrix::Matrix(int row, int column, const int** elements)
{
	rows = row;
	columns = column;
	data = (int**) new int* [rows];
	for (int i = 0; i < rows; i++)
		data[i] = new int[columns];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			data[i][j] = elements[i][j];
}