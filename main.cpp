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
  S21Matrix test1;

        test1.SetRows(1);
}