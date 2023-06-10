#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>
#include <cmath>

class S21Matrix {

 public:
	S21Matrix();
	S21Matrix(int rows, int cols);
	S21Matrix(const S21Matrix& other); // переписать
	S21Matrix(S21Matrix&& other); // переписать
	~S21Matrix();

	bool EqMatrix(const S21Matrix& other) const;
	void SumMatrix(const S21Matrix& other);
	void SubMatrix(const S21Matrix& other);
	void MulNumber(const double num);
	void MulMatrix(const S21Matrix& other);
	S21Matrix Transpose() const;
	double Determinant() const;
	S21Matrix CalcComplements() const;
	S21Matrix InverseMatrix() const;

	S21Matrix& operator=(const S21Matrix& other);
	S21Matrix& operator+=(const S21Matrix& other);
	S21Matrix& operator-=(const S21Matrix& other);
	S21Matrix& operator*=(const S21Matrix& other);
  double operator()(int i, int j);
  double operator()(int i, int j) const;
	double* operator[](int row);
	double* operator[](int row) const;
	int GetRows() const;
	int GetCols() const;
	void SetRows(const int rows);
	void SetCols(const int cols);
	
 private:
  int rows_ = 0;
  int cols_ = 0;
  double** matrix_ = nullptr;
	S21Matrix getMatrix(int row, int col) const;
	void clean();
};

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator*(const double lhs, const S21Matrix& rhs); // TODO
bool operator==(const S21Matrix& lhs, const S21Matrix& rhs);

#endif
