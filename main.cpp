#include <iostream>
#include <vector>
#include "s21_matrix_oop.h"

int main() {
  auto test = S21Matrix(3, 3);
  test[0][0] = 1;
  S21Matrix tmp;

  tmp = test;
  
}