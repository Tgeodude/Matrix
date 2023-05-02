#include "s21_matrix_oop.h"
#include <iostream>
#include <cmath>

S21Matrix::S21Matrix() {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
}

S21Matrix::S21Matrix(const int rows, const int cols) {
    this -> ~S21Matrix();
    if (rows < 1 || cols < 1) {
        throw std::logic_error("Invalid matrix size");
    }
    rows_ = rows;
    cols_ = cols;
    matrix_ = (double**)malloc(rows * sizeof(double*));
    if (!matrix_) {
        throw "Can't allocate memory";
    }
    for (int i = 0; i < cols; i++) {
        matrix_[i] = (double*)malloc(cols * sizeof(double));
        if (!matrix_) {
            throw "Can't allocate memory";
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix_[i][j] = 0;
        }
    }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    operator=(other);
}

S21Matrix::S21Matrix(S21Matrix& other) {
    this -> ~S21Matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    if (isValidMatrix()) {
        for (int i = 0; i < rows_; i++) {
            free(matrix_[i]);
        }
        free(matrix_);
    }
}

S21Matrix &S21Matrix::operator=(const S21Matrix& other) {
    if (!other.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (this != &other) {
        this -> ~S21Matrix();
        auto temp = S21Matrix(other.rows_, other.cols_);
        for (int i = 0; i < temp.rows_; i++) {
            for (int j = 0; j < temp.cols_; j++) {
                temp.matrix_[i][j] = other.matrix_[i][j];
            }
        }
        rows_ = temp.rows_;
        cols_ = temp.cols_;
        matrix_ = temp.matrix_;
        temp.matrix_ = nullptr;
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const double& other) {
    MulNumber(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

double& S21Matrix::operator()(int i, int j) {
    if (i >= rows_ || j >= cols_) {
        throw std::logic_error("Invalid index");
    }
    return matrix_[i][j];
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const{
    if (!isValidMatrix() || !other.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (matrix_[i][j] != other.matrix_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (!isValidMatrix() || !other.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::logic_error("Invalid operation");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (!isValidMatrix() || !other.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::logic_error("Invalid operation");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double& other) {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= other;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (!isValidMatrix() || !other.isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (cols_ != other.rows_) {
        throw std::logic_error("Invalid operation");
    }
    S21Matrix result = S21Matrix(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = S21Matrix(std::move(result));
}

S21Matrix S21Matrix::Transpose() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    S21Matrix result = S21Matrix(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}


double S21Matrix::Determinant() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != cols_) {
        throw std::logic_error("Invalid operation");
    }
    double det = 1.0;
    double **temp = (double**) malloc(rows_ * sizeof(double*));
    for (int i = 0; i < rows_; i++) {
        temp[i] = (double*) malloc(rows_ * sizeof(double));
        for (int j = 0; j < rows_; j++) {
            temp[i][j] = matrix_[i][j];
        }
    }
    for (int k = 0; k < rows_ - 1; k++) {
        int max_row = k;
        double max_val = std::abs(temp[k][k]);
        for (int i = k + 1; i < rows_; i++) {
            if (std::abs(temp[i][k]) > max_val) {
                max_val = std::abs(temp[i][k]);
                max_row = i;
            }
        }
        if (max_val == 0.0) {
            return 0.0;
        }
        if (max_row != k) {
            det = -det;
            std::swap(temp[k], temp[max_row]);
        }
        for (int i = k + 1; i < rows_; i++) {
            double f = temp[i][k] / temp[k][k];
            for (int j = k + 1; j < rows_; j++) {
                temp[i][j] -= f * temp[k][j];
            }
            temp[i][k] = 0.0;
        }
        det *= temp[k][k];
    }
    det *= temp[rows_-1][rows_-1];
    free(temp);
    return det;
}

S21Matrix S21Matrix::InverseMatrix() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != cols_) {
        throw std::logic_error("Invalid operation");
    }
    double matrixDeterminant = Determinant();
    if (fabs(matrixDeterminant - 0) <= 1E-7) {
        throw std::logic_error("Invalid operation");
    }
    S21Matrix result = CalcComplements().Transpose();
    result.MulNumber(1/matrixDeterminant);
    return result;
}

S21Matrix S21Matrix::CalcComplements() const {
    if (!isValidMatrix()) {
        throw std::logic_error("Invalid matrix");
    }
    if (rows_ != cols_) {
        throw std::logic_error("Invalid operation");
    }
    S21Matrix result = S21Matrix(rows_, rows_);
    if (rows_ == 1) {
        result.matrix_[0][0] = matrix_[0][0];
        return result;
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[i][j] = pow(-1, i * rows_ + j) * getMatrixForMinor(i, j).Determinant();
        }
    }
    return result;
}

S21Matrix S21Matrix::getMatrixForMinor(int row, int col) const {
    S21Matrix result = S21Matrix(rows_ - 1, cols_ - 1);
    int new_i = 0;
    for (int i = 0; i < rows_; i++) {
        if (i != row) {
            int new_j = 0;
            for (int j = 0; j < cols_; j++) {
                if (j != col) {
                    result.matrix_[new_i][new_j] = matrix_[i][j];
                    new_j++;
                }
            }
            new_i++;
        }
    }
    return result;
}

int S21Matrix::GetRows() const {
    return rows_;
}

int S21Matrix::GetCols() const {
    return cols_;
}

void S21Matrix::SetRows(const int rows) {
    this -> rows_ = rows;
}

void S21Matrix::SetCols(const int cols) {
    this -> cols_ = cols;
}

bool S21Matrix::isValidMatrix() const {
    return matrix_ != nullptr;
}

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& other) {
    S21Matrix result = lhs;
    result += other;
    return result;
}

S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& other) {
    S21Matrix result = lhs;
    result -= other;
    return result;
}

S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& other) {
    S21Matrix result = lhs;
    result *= other;
    return result;
}

S21Matrix operator*(const S21Matrix& lhs, const double& other) {
    S21Matrix result = lhs;
    result *= other;
    return result;
}

S21Matrix operator* (const double& lhs, const S21Matrix& other) {
    S21Matrix result = other;
    result *= lhs;
    return result;
}

bool operator==(const S21Matrix& lhs, const S21Matrix& other) {
    return lhs.EqMatrix(other);
}