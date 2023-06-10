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
  test1[1][1] = 5;
  auto test2 = S21Matrix(test1);
  auto test3 = std::move(test1);  
  echoMatrix(test1);
  echoMatrix(test2);
  echoMatrix(test3);

  std::cout<<"end"<<std::endl;
}