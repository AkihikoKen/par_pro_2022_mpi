// Copyright 2022 Bugrov Andrey

#include "../../../modules/task_1/bugrov_a_min_value_in_matrix/min_value_in_matrix.h"

#include <mpi.h>  // for mpi

#include <ctime>  // for time function
#include <random>  // for mt19937

void CreateRandomValues(int* matrix, int size) {
  std::mt19937 engine(time(0));
  for (int i = 0; i < size; i++) {
    matrix[i] = engine() % 100000;
  }
}


int SeqMinValue(int* matrix, int size) {
  int min_value = matrix[0];
  int i = 1;
  for (; i < size; i++) {
    if (matrix[i] < min_value) {
      min_value = matrix[i];
    }
  }
  return min_value;
}

// result is in min_values[0]
int ParMinValue(int* matrix, int size, int process_num) {
  int rank = 0;
  int part = size / process_num;
  int min_values[process_num];
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    int i = 0;
    for (; i < process_num - 1; i++) {
      MPI_Send(matrix + i * part, part, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
    }
    min_values[0] = matrix[(process_num - 1) * part];
    for (i = (process_num - 1) * part + 1; i < size; i++) {
      if (min_values[0] > matrix[i]) {
        min_values[0] = matrix[i];
      }
    }
    for (int i = 1; i < process_num; i++) {
      MPI_Recv(min_values + i, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD,
               &status);
      if (min_values[0] > min_values[i]) {
        min_values[0] = min_values[i];
      }
    }
  } else {
    if (rank < process_num) {
      int* recv_buf;
      recv_buf = new int[part];
      int* tmp_result = new int;
      MPI_Recv(recv_buf, part, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      *tmp_result = recv_buf[0];
      int i = 1;
      min_values[rank] = recv_buf[0];
      for (; i < part; i++) {
        /*if (min_values[rank] > recv_buf[i]) {
            min_values[rank] = recv_buf[i];
        }*/
        if (*tmp_result > recv_buf[i]) {
          *tmp_result = recv_buf[i];
        }
      }
      MPI_Send(tmp_result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  }
  return min_values[0];
}
