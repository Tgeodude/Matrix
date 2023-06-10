#include <iostream>
#include <vector>
#include "s21_matrix_oop.h"

int main() {
  auto test1 = S21Matrix(3, 3);
  test1[1][1] = 5;
  auto test2 = S21Matrix(test1);
  std::cout<<"Hello"<<std::endl;
  auto test3 = std::move(test1);
  return 0;
}