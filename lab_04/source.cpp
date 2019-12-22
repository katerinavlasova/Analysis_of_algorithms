#include "matrix_class.h"           


int** input(int* prow, int* pcol)
{
	std::cout << "Input rows of matrix:";
	scanf_s("%d", prow);
	std::cout << "Input columns of matrix:";
	scanf_s("%d", pcol);
	int b;
	int** data = (int**) new int* [*prow];
	for (int i = 0; i < *prow; i++)
		data[i] = new int[*pcol];
	for (int i = 0; i < *prow; i++)
		for (int j = 0; j < *pcol; j++)
		{
			std::cout << "Input elenemt:";
			scanf_s("%d", &b);
			data[i][j] = b;
		}
	return data;
}

int** fill_matrix(int size)
{
	int** data = (int**) new int* [size];
	int b;
	for (int i = 0; i < size; i++)
		data[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			b = rand();
			data[i][j] = b;
		}
	return data;
}

void show_matrix(int row, int column, const int** data)
{
	for (int i = 0; i < row; i++)
	{
		printf("\n");
		for (int j = 0; j < column; j++)
			printf("%d ", data[i][j]);
	}
}

int** classic_mult(Matrix& matr1, Matrix& matr2)
{
	int r = matr1.rows;
	int c = matr2.columns;
	int** data = (int**) new int* [r];
	for (int i = 0; i < r; i++)
		data[i] = new int[c];

	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			data[i][j] = 0;
			for (int k = 0; k < matr1.columns; k++)
				data[i][j] += matr1.data[i][k] * matr2.data[k][j];
		}
	return data;
}

int** winograd(Matrix& matr1, Matrix& matr2, int** data)
{
	size_t* res = nullptr;
	int r = matr1.rows;
	int c = matr2.columns;
	int* mulh = new int[r];
	for (int i = 0; i < r; i++) {
		mulh[i] = matr1.data[i][0] * matr1.data[i][1];
		for (int j = 2; j <= matr2.rows / 2; j++)
		{
			mulh[i] = mulh[i] + matr1.data[i][2 * j - 2] * matr1.data[i][2 * j - 1];
		}
	}
	int* mulv = new int[c];
	for (int i = 0; i < c; i++) {
		mulv[i] = matr2.data[0][i] * matr2.data[1][i];
		for (int j = 2; j <= matr2.rows / 2; j++)
			mulv[i] = mulv[i] + matr2.data[2 * j - 2][i] * matr2.data[2 * j - 1][i];
	}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++) {
			data[i][j] = -mulh[i] - mulv[j];
			for (int k = 1; k <= matr2.rows / 2; k++)
				data[i][j] = data[i][j] + \
				(matr1.data[i][2 * k - 2] + matr2.data[2 * k - 1][j]) * (matr1.data[i][2 * k - 1] + \
					matr2.data[2 * k - 2][j]);
		}
	if (r % 2 != 0)
	{
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				data[i][j] = data[i][j] + matr1.data[i][matr2.rows - 1] *
				matr2.data[matr2.rows - 1][j];
	}
	delete[]mulv;
	delete[]mulh;
	return data;
}

void paral(Matrix& matr1, Matrix& matr2, int** data, int* mulh, int* mulv, int num, int NThread)
{
	for (int i = num; i < matr1.rows; i += NThread)
		for (int j = 0; j < matr2.columns; j++) {
			data[i][j] = -mulh[i] - mulv[j];
			for (int k = 1; k <= matr2.rows / 2; k++)
				data[i][j] = data[i][j] + \
				(matr1.data[i][2 * k - 2] + matr2.data[2 * k - 1][j]) * (matr1.data[i][2 * k - 1] + \
					matr2.data[2 * k - 2][j]);
		}
}

int** parall_winograd(Matrix& matr1, Matrix& matr2, int** data, int NThreads)
{
	size_t* res = nullptr;
	int r = matr1.rows;
	int c = matr2.columns;
	int* mulh = new int[r];
	for (int i = 0; i < r; i++) {
		mulh[i] = matr1.data[i][0] * matr1.data[i][1];
		for (int j = 2; j <= matr2.rows / 2; j++)
		{
			mulh[i] = mulh[i] + matr1.data[i][2 * j - 2] * matr1.data[i][2 * j - 1];
		}
	}
	int* mulv = new int[c];
	for (int i = 0; i < c; i++) {
		mulv[i] = matr2.data[0][i] * matr2.data[1][i];
		for (int j = 2; j <= matr2.rows / 2; j++)
			mulv[i] = mulv[i] + matr2.data[2 * j - 2][i] * matr2.data[2 * j - 1][i];
	}

	thread* t = new thread[NThreads];
	for (int i = 0; i < NThreads; i++)
		t[i] = thread(&paral, ref(matr1), ref(matr2), data, &mulh[0], &mulv[0], i, NThreads);
	for (int i = 0; i < NThreads; i++)
	{
		if (t[i].joinable())
			t[i].join();
	}

	if (r % 2 != 0)
	{
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				data[i][j] = data[i][j] + matr1.data[i][matr2.rows - 1] *
				matr2.data[matr2.rows - 1][j];
	}
	delete[]mulv;
	delete[]mulh;
	return data;
}



int main()
{
	int row1, column1;
	int* prow1 = &row1;
	int* pcol1 = &column1;
	printf("Choose mode:\n1.User mode.\n2.Experimental mode.\nNumber: ");
	int mode;
	scanf_s("%d", &mode);
	if (mode == 1)
	{
		int** elements1 = input(prow1, pcol1);
		Matrix A(row1, column1, (const int**)elements1);
		for (int i = 0; i < row1; i++)
			delete[] elements1[i];
		int row2, column2;
		int* prow2 = &row2;
		int* pcol2 = &column2;
		int** elements2 = input(prow2, pcol2);
		Matrix B(row2, column2, (const int**)elements2);
		for (int i = 0; i < row2; i++)
			delete[] elements2[i];
		std::cout << "First matrix:";
		A.show_mtrx();
		std::cout << "\nSecond matrix:";
		B.show_mtrx();
		printf("\nNumber of threads:");
		int NThreads;
		scanf_s("%d", &NThreads);
		// iau?iia oiii?
		int** res = classic_mult(A, B);
		Matrix C(row1, column2, (const int**)res);
		for (int i = 0; i < row1; i++)
			delete[] res[i];
		std::cout << "Classic mult:\n";
		C.show_mtrx();
		// iau?iue aeiia?aa
		unsigned long long start_time = clock();
		int** data = (int**) new int* [row1];
		for (int i = 0; i < row1; i++)
			data[i] = new int[column2];
		int** res2 = winograd(A, B, data);
		unsigned long long end_time = clock();
		unsigned long long search_time = end_time - start_time;
		Matrix D(row1, column2, (const int**)res2);
		std::cout << "\n\nWinograd:";
		D.show_mtrx();
		std::cout << "\n\nParall. Winograd:";
		start_time = clock();
		int** result = parall_winograd(A, B, data, NThreads);
		end_time = clock();
		search_time = end_time - start_time;
		show_matrix(row1, column2, (const int**)result);
	}
	else
	{
		printf("Size of matrix:");
		int size;
		scanf_s("%d", &size);
		printf("\nNumber of threads:");
		int NThreads;
		scanf_s("%d", &NThreads);
		int** res1 = fill_matrix(size);
		int** res2 = fill_matrix(size);
		Matrix A(size, size, (const int**)res1);
		Matrix B(size, size, (const int**)res2);
		int** data = (int**) new int* [size];
		for (int i = 0; i < size; i++)
			data[i] = new int[size];
		auto begin = std::chrono::steady_clock::now();
		int** result1 = winograd(A, B, data);
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "The time for Winograd: " << elapsed_ms.count() << " ms\n";

		begin = std::chrono::steady_clock::now();
		int** result2 = parall_winograd(A, B, data, NThreads);
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << "The time for parall. Winograd: " << elapsed_ms.count() << " ms\n";
	}
	return 0;
}