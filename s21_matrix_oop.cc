#include "s21_matrix_oop.h"



S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Wrong matrix size");
  }

  rows_ = rows;
  cols_ = cols;

  matrix_ = new double*[rows_];

  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

S21Matrix::S21Matrix(const S21Matrix& other) : S21Matrix(other.rows_, other.cols_) { operator=(other); }

S21Matrix::S21Matrix(S21Matrix&& other) : S21Matrix(other.rows_, other.cols_) {
  matrix_ = other.matrix_;

  other = S21Matrix();
}

void S21Matrix::clean() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }

  delete[] matrix_;
}

S21Matrix::~S21Matrix() {
  clean();
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other[i][j]) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Wrong operation");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Wrong operation");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Wrong operation");
  }

  S21Matrix newMatrix = S21Matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        newMatrix[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = std::move(newMatrix);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix newMatrix = S21Matrix(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      newMatrix[j][i] = matrix_[i][j];
    }
  }

  return newMatrix;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }

  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];;
  }

  double det = 0;

  for (int c = 0; c < cols_; c++) {
    auto subMatrix = S21Matrix(rows_ - 1, cols_ - 1);
    for (int r = 1; r < rows_; r++) {
      for (int col = 0, subcol = 0; col < cols_; col++) {
        if (col != c) {
          subMatrix[r - 1][subcol] = matrix_[r][col];
          subcol++;
        }
      }
    }

    int sign = (c % 2 == 0) ? 1 : -1;
    double subDet = subMatrix.Determinant();
    det += sign * matrix_[0][c] * subDet;
  }

  return det;
}

S21Matrix S21Matrix::getMatrix(int row, int col) const {
  int matrixRows = 0;
  int matrixCols = 0;
  auto resultMatrix = S21Matrix(row, col);

  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;
    matrixCols = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == col) continue;
      resultMatrix[matrixRows][matrixCols] = matrix_[i][j];
      matrixCols++;
    }
    matrixRows++;
  }

  return resultMatrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Invalid argument matrix: rows != cols");
  }

  S21Matrix res(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  double determinant = 0.0;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor = getMatrix(i, j);
      determinant = minor.Determinant();
      res.matrix_[i][j] = pow(-1, i + j) * determinant;
    }
  }

  return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Invalid argument matrix: rows != cols");
  }

  double determinant = Determinant();
  if (std::fabs(determinant) < 1e-7) {
    throw std::invalid_argument("Invalid argument");
  }

  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    res = tmp.Transpose();
    res.MulNumber(1 / determinant);
  }

  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  SetRows(other.GetRows());
  SetCols(other.GetCols());

  rows_ = other.rows_;
  cols_ = other.cols_;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);

  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);

  return *this;
}

double S21Matrix::operator()(int i, int j) {
  return *this[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  return *this[i][j];
}

double* S21Matrix::operator[](int row) {
  if (rows_ <= row) {
    throw std::invalid_argument("bad agrument");
  }

  return matrix_[row];
}

double* S21Matrix::operator[](int row) const {
  if (rows_ <= row) {
    throw std::invalid_argument("bad agrument");
  }

  return matrix_[row];
}

int S21Matrix::GetRows() const {
  return rows_;
}

int S21Matrix::GetCols() const {
  return cols_;
}

void S21Matrix::SetRows(int rows) {
  if (rows == rows_) {
    return;
  }

  auto newMatrix = S21Matrix(rows, cols_);

  auto newRows = 0;

  if (rows_ < rows) {
    newRows = rows_;
  } else {
    newRows = rows;
  }

  for (int i = 0; i < newRows; i++) {
    for (int j = 0; j < cols_; j++) {
      newMatrix[i][j] = matrix_[i][j];
    }
  }

  *this = std::move(newMatrix);
}

void S21Matrix::SetCols(int cols) {
  if (cols == cols_) {
    return;
  }

  auto newMatrix = S21Matrix(rows_, cols);

  auto newCols = 0;

  if (cols_ < cols) {
    newCols = cols_;
  } else {
    newCols = cols;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < newCols; j++) {
      newMatrix[i][j] = matrix_[i][j];
    }
  }

  *this = std::move(newMatrix);
}

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs) {
  auto newMatrix = S21Matrix(lhs);
  newMatrix += rhs;

  return newMatrix;
}

S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs) {
  auto newMatrix = S21Matrix(lhs);
  newMatrix -= rhs;

  return newMatrix;
}

S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs) {
  auto newMatrix = S21Matrix(lhs);
  newMatrix *= rhs;

  return newMatrix;
}

S21Matrix operator*(const double lhs, const S21Matrix& rhs) {
  auto newMatrix = S21Matrix(rhs);
  newMatrix.MulNumber(lhs);

  return newMatrix;
}

bool operator==(const S21Matrix& lhs, const S21Matrix& rhs) {
  return lhs.EqMatrix(rhs);
}
