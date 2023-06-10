#include <iostream>
#include <vector>
#include "s21_matrix_oop.h"

void echoMatrix(const S21Matrix& a) {
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      std::cout<<a[i][j]<<" ";
    }
    std::cout<<std::endl;
  }
}

int main() {
  auto test1 = S21Matrix(3, 3);
  for (int i = 0; i < test1.GetRows(); i++) {
      for (int j = 0; j < test1.GetCols(); j++) {
          test1[i][j] = test1.GetRows() * i + j + 1;
      }
  }
  auto test2 = test1;
  test1.MulMatrix(test2);
  test2[0][0] = 30;
  test2[0][1] = 36;
  test2[0][2] = 42;
  test2[1][0] = 66;
  test2[1][1] = 81;
  test2[1][2] = 96;
  test2[2][0] = 102;
  test2[2][1] = 126;
  test2[2][2] = 150;

  echoMatrix(test1);
  std::cout<<"--------------"<<std::endl;
  echoMatrix(test2);
}