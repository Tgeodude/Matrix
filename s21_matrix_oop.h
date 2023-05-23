#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>
#include <cmath>

class S21Matrix {

    private:
        int rows_ = 0;
        int cols_ = 0;
        double** matrix_ = nullptr;
		bool isValid() const;
		void getMatrix(int row, int col, const S21Matrix& tmp);
		double getDeterminant();
    public:
		S21Matrix();
		S21Matrix(int rows, int cols);
		S21Matrix(const S21Matrix& other);
		S21Matrix(S21Matrix&& other);
		~S21Matrix();

		bool EqMatrix(const S21Matrix& other) const;
		void SumMatrix(const S21Matrix& other);
		void SubMatrix(const S21Matrix& other);
		void MulNumber(const double num);
		void MulMatrix(const S21Matrix& other);
		S21Matrix Transpose();
		double Determinant();
		S21Matrix CalcComplements();
		S21Matrix InverseMatrix();

		S21Matrix& operator=(const S21Matrix& other);
		S21Matrix& operator+=(const S21Matrix& other);
		S21Matrix& operator-=(const S21Matrix& other);
		S21Matrix& operator*=(const S21Matrix& other);
    	double& operator()(int i, int j);
		int getRows() const;
		int getCols() const;
		void setRows(const int rows);
		void setCols(const int cols);
};

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs);
S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs);
bool operator==(const S21Matrix& lhs, const S21Matrix& rhs);

#endif
