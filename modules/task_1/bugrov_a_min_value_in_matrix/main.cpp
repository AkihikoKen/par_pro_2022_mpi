// Copyright 2022 Bugrov Andrey

#include <gtest/gtest.h>

#include <gtest-mpi-listener.hpp>

#include "./min_value_in_matrix.h"

// TEST(min_value_in_matrix, small_matr_no_reminder_2_proc) {
//  int rank;
//  int min_value_seq, min_value_par;
//  const int kSize = 500;
//  int matrix[kSize];
//  const int proc_num = 2;
//  int min_values[proc_num];
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//  if (rank == 0) {
//    CreateRandomValues(matrix, kSize);
//  }
//  ParMinValue(matrix, kSize, proc_num, min_values);
//  min_value_par = min_values[0];
//  if (rank == 0) {
//    min_value_seq = SeqMinValue(matrix, kSize);
//    EXPECT_EQ(min_value_par, min_value_seq);
//  }
//}
//
// TEST(min_value_in_matrix, big_matr_coprime_integers_4_proc) {
//  int rank;
//  int min_value_seq, min_value_par;
//  const int kSize = 998001;
//  int matrix[kSize];
//  const int proc_num = 2;
//  int min_values[proc_num];
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//  if (rank == 0) {
//    CreateRandomValues(matrix, kSize);
//  }
//  ParMinValue(matrix, kSize, proc_num, min_values);
//  min_value_par = min_values[0];
//  if (rank == 0) {
//    min_value_seq = SeqMinValue(matrix, kSize);
//    EXPECT_EQ(min_value_par, min_value_seq);
//  }
//}
//
// TEST(min_value_in_matrix, big_matr_coprime_integers_3_proc) {
//  int rank;
//  int min_value_seq, min_value_par;
//  const int kSize = 1000000;
//  int matrix[kSize];
//  const int proc_num = 3;
//  int min_values[proc_num];
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//  if (rank == 0) {
//    CreateRandomValues(matrix, kSize);
//  }
//  ParMinValue(matrix, kSize, proc_num, min_values);
//  min_value_par = min_values[0];
//  if (rank == 0) {
//    min_value_seq = SeqMinValue(matrix, kSize);
//    EXPECT_EQ(min_value_par, min_value_seq);
//  }
//}
// TEST(min_value_in_matrix, big_matr_coprime_integers_10_proc) {
//  int rank;
//  int min_value_seq, min_value_par;
//  const int kSize = 1000998;
//  int matrix[kSize];
//  const int proc_num = 10;
//  int min_values[proc_num];
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//  CreateRandomValues(matrix, kSize);
//  ParMinValue(matrix, kSize, proc_num, min_values);
//  min_value_par = min_values[0];
//  if (rank == 0) {
//    min_value_seq = SeqMinValue(matrix, kSize);
//    EXPECT_EQ(min_value_par, min_value_seq);
//  }
//}
// TEST(min_value_in_matrix, big_matr_1_proc) {
//  int rank;
//  int min_value_seq, min_value_par;
//  const int kSize = 1000998;
//  int matrix[kSize];
//  const int proc_num = 1;
//  int min_values[proc_num];
//  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//  CreateRandomValues(matrix, kSize);
//  ParMinValue(matrix, kSize, proc_num, min_values);
//  min_value_par = min_values[0];
//  if (rank == 0) {
//    min_value_seq = SeqMinValue(matrix, kSize);
//    EXPECT_EQ(min_value_par, min_value_seq);
//  }
//}

TEST(min_value_in_matrix, equal_values) {
  int i;
  int rank;
  int min_value_seq, min_value_par;
  const int kSize = 100;
  int matrix[kSize];
  int proc_num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  if (rank == 0) {
    for (i = 0; i < kSize; i++) {
      matrix[i] = 1;
    }
  }
  min_value_par = ParMinValue(matrix, kSize, proc_num);
  if (rank == 0) {
    min_value_seq = SeqMinValue(matrix, kSize);
    EXPECT_EQ(min_value_par, min_value_seq);
  }
}

TEST(min_value_in_matrix, in_order_of_producing) {
  int i;
  int rank;
  int min_value_seq, min_value_par;
  const int kSize = 100;
  int matrix[kSize];
  int proc_num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  if (rank == 0) {
    for (i = 0; i < kSize; i++) {
      matrix[i] = i;
    }
  }
  min_value_par = ParMinValue(matrix, kSize, proc_num);
  if (rank == 0) {
    min_value_seq = SeqMinValue(matrix, kSize);
    EXPECT_EQ(min_value_par, min_value_seq);
  }
}

TEST(min_value_in_matrix, in_order_of_reducing) {
  int i;
  int rank;
  int min_value_seq, min_value_par;
  const int kSize = 100;
  int matrix[kSize];
  int proc_num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  if (rank == 0) {
    for (i = 0; i < kSize; i++) {
      matrix[i] = kSize - i;
    }
  }
  min_value_par = ParMinValue(matrix, kSize, proc_num);
  if (rank == 0) {
    min_value_seq = SeqMinValue(matrix, kSize);
    EXPECT_EQ(min_value_par, min_value_seq);
  }
}

TEST(min_value_in_matrix, random_small) {
  int rank;
  int min_value_seq, min_value_par;
  const int kSize = 100;
  int matrix[kSize];
  int proc_num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  if (rank == 0) {
    CreateRandomValues(matrix, kSize);
  }
  min_value_par = ParMinValue(matrix, kSize, proc_num);
  if (rank == 0) {
    min_value_seq = SeqMinValue(matrix, kSize);
    EXPECT_EQ(min_value_par, min_value_seq);
  }
}

TEST(min_value_in_matrix, random_prime) {
  int rank;
  int min_value_seq, min_value_par;
  const int kSize = 997;
  int matrix[kSize];
  int proc_num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  if (rank == 0) {
    CreateRandomValues(matrix, kSize);
  }
  min_value_par = ParMinValue(matrix, kSize, proc_num);
  if (rank == 0) {
    min_value_seq = SeqMinValue(matrix, kSize);
    EXPECT_EQ(min_value_par, min_value_seq);
  }
}

TEST(min_value_in_matrix, random_huge) {
  int rank;
  int min_value_seq, min_value_par;
  const int kSize = 10934099;  // 997*997*11
  int* matrix = new int[kSize];
  int proc_num;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
  if (rank == 0) {
    CreateRandomValues(matrix, kSize);
  }
  min_value_par = ParMinValue(matrix, kSize, proc_num);
  if (rank == 0) {
    min_value_seq = SeqMinValue(matrix, kSize);
    EXPECT_EQ(min_value_par, min_value_seq);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  MPI_Init(&argc, &argv);

  ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  listeners.Release(listeners.default_result_printer());
  listeners.Release(listeners.default_xml_generator());

  listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
  return RUN_ALL_TESTS();
}
