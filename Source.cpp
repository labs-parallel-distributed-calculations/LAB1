#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

#define BASIS_RANDOM_NUMBER 60
#define MIN_RANDOM_NUMBER -30

void generate_matrix(int *output_matrix, int height, int length) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < length; ++j) {
			*(output_matrix+i*length+j) = rand() % BASIS_RANDOM_NUMBER + MIN_RANDOM_NUMBER;
		}
	}
}

vector<int> get_numbers_under_matrix_diagonal(int *matrix, int height, int length) {
	vector<int> result;
	for (int i = 1; i < height; ++i) {
		for (int j = 0; j < i; ++j) {
			result.push_back(*(matrix + i * length + j));
		}
	}
	return result;
}

void first_task() {
	int array_height = 1;
	int array_length = 10;
	int * C = (int *)malloc(array_height*array_length * sizeof(int));
	generate_matrix(C, array_height, array_length);
	int sum = 0;
	for (int i = 0; i < array_length; ++i) {
		if (*(C + i) % 3) {
			sum += *(C + i);
		}
	}
	cout << "First task executed, result: " << sum << endl;
}

void second_task() {
	int matrix_height = 5;
	int matrix_length = 5;
	int * C = (int *)malloc(matrix_height*matrix_length * sizeof(int));
	generate_matrix(C, matrix_height, matrix_length);
	vector<int> elements_under_diagonal = get_numbers_under_matrix_diagonal(C, matrix_height, matrix_length);
	int sum = 0, count = 0;
	for (auto i : elements_under_diagonal) {
		if (i < 0) {
			sum += i;
			++count;
		}
	}
	cout << "Second task executed, result: " << sum << " ; " << count << endl;
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv); int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) {
		first_task();
	}
	else if (rank == 1) {
		second_task();
	}
	MPI_Finalize();
	return 0;
}
