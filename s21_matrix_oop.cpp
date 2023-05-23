#include "s21_matrix_oop.h"

//------------------------------------------------------------------------------------------------------------------------
//PRIVATE
//------------------------------------------------------------------------------------------------------------------------

bool S21Matrix::isValid() const {
    return matrix_ != nullptr;
}

void S21Matrix::getMatrix(int row, int col, const S21Matrix& tmp) {
	int matrixRows = 0;
	int matrixCols = 0;
	for (int i = 0; i < rows_; i++) {
		if (i == row)
			continue;
		matrixCols = 0;
		for (int j = 0; j < cols_; j++) {
			if (j == col)
				continue;
			tmp.matrix_[matrixRows][matrixCols] = matrix_[i][j];
			matrixCols++;
		}
		matrixRows++;
	}
}

double S21Matrix::getDeterminant() {
	double res = 0.0;
	if (rows_ == 1)
		res = matrix_[0][0];
	else {
		S21Matrix tmp(rows_ - 1, cols_ - 1);
		for (int i = 0; i < cols_; i++) {
			getMatrix(0, i, tmp);
			if (i % 2)
				res -= matrix_[0][i] * tmp.getDeterminant();
			else
				res += matrix_[0][i] * tmp.getDeterminant();
		}
	}
	return res;
}



//------------------------------------------------------------------------------------------------------------------------
//PUBLIC
//------------------------------------------------------------------------------------------------------------------------

S21Matrix::S21Matrix() : rows_{0}, cols_{0}, matrix_{nullptr} {}

S21Matrix::S21Matrix(int rows, int cols) {
    this -> ~S21Matrix();
    if (rows < 1 && cols < 1)
        throw std::invalid_argument("Invalid argument: rows and cols < 1");
    rows_ = rows;
    cols_ = cols;
    matrix_ = (double**)malloc(rows * sizeof(double*));
    if (!matrix_)
	    	throw std::invalid_argument("Invalid matrix");
    for (int i = 0; i < cols; i++) {
        matrix_[i] = (double*)malloc(cols * sizeof(double));
	    if (!matrix_)
		    throw std::invalid_argument("Invalid matrix");
    	for (int j = 0; j < cols; j++) {
		    matrix_[i][j] = 0;
	    }
    }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    if (!other.isValid())
        throw std::invalid_argument("Invalid matrix");
    if (this != &other) {
        S21Matrix tmp(other.rows_, other.cols_);
        for (int i = 0; i < tmp.rows_; i++) {
            for (int j = 0; j < tmp.cols_; j++) {
                tmp.matrix_[i][j] = other.matrix_[i][j];
            }
        }
        rows_ = tmp.rows_;
        cols_ = tmp.cols_;
        matrix_ = tmp.matrix_;
		tmp.matrix_ = nullptr;
	}
}

S21Matrix::S21Matrix(S21Matrix&& other) {
	this -> ~S21Matrix();
	rows_ = other.rows_;
	cols_ = other.cols_;
	matrix_ = other.matrix_;
	other.rows_ = 0;
	other.cols_ = 0;
	other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    if (isValid()) {
	    for (int i = 0; i < rows_; i++) {
		    free(matrix_[i]);
	    }
    free(matrix_);
    }
}



//------------------------------------------------------------------------------------------------------------------------
//MATRIX FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------


bool S21Matrix::EqMatrix(const S21Matrix& other) const {
    if (!isValid() || !other.isValid())
		throw std::invalid_argument("Invalid matrix");
	if (rows_ != other.rows_ || cols_ != other.cols_)
		return false;
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			if (matrix_[i][j] != other.matrix_[i][j])
				return false;
		}
	}
	return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
	if (!isValid() || !other.isValid())
		throw std::invalid_argument("Invalid matrix");
	if (rows_ != other.rows_ || cols_ != other.cols_)
		throw std::invalid_argument("Invalid argument");
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			matrix_[i][j] += other.matrix_[i][j];
		}
	}
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
	if (!isValid() || !other.isValid())
		throw std::invalid_argument("Invalid matrix");
	if (rows_ != other.rows_ || cols_ != other.cols_)
		throw std::invalid_argument("Invalid argument");
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			matrix_[i][j] -= other.matrix_[i][j];
		}
	}
}

void S21Matrix::MulNumber(const double num) {
	if (!isValid())
		throw std::invalid_argument("Invalid matrix");
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			matrix_[i][j] *= num;
		}
	}
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
	if (!isValid() || !other.isValid())
		throw std::invalid_argument("Invalid matrix");
	if (cols_ != other.rows_) {
    	throw std::invalid_argument("Invalid argument: matrix1.cols != matrix2.cols");
	}
	S21Matrix res(rows_, other.cols_);
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < other.cols_; j++) {
			for (int k = 0; k < cols_; k++) {
				res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
			}
		}
	}
	*this = S21Matrix(std::move(res));
}

S21Matrix S21Matrix::Transpose() {
	if (!isValid())
		throw std::invalid_argument("Invalid matrix");
	S21Matrix res(cols_, rows_);
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			res.matrix_[j][i] = matrix_[i][j];
		}
	}
	return res;
}

double S21Matrix::Determinant() {
	if (!isValid())
    	throw std::invalid_argument("Invalid matrix");
	if (rows_ != cols_)
    	throw std::invalid_argument("Invalid argument matrix: rows != cols");
	return getDeterminant();
}

S21Matrix S21Matrix::CalcComplements() {
	if (!isValid())
    	throw std::invalid_argument("Invalid matrix");
	if (rows_ != cols_)
    	throw std::invalid_argument("Invalid argument matrix: rows != cols");
	S21Matrix res(rows_, cols_);
	S21Matrix minor(rows_ - 1, cols_ - 1);
	double determinant = 0.0;
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			getMatrix(i, j, minor);
			determinant = minor.Determinant();
			res.matrix_[i][j] = pow(-1, i + j) * determinant;
		}
	}
	return res;
}

S21Matrix S21Matrix::InverseMatrix() {
	if (!isValid())
    	throw std::invalid_argument("Invalid matrix");
	if (rows_ != cols_)
    	throw std::invalid_argument("Invalid argument matrix: rows != cols");
	double determinant = Determinant();
	if (std::fabs(determinant) < 1e-7)
    	throw std::invalid_argument("Invalid argument");
	S21Matrix res(rows_, cols_);
	if (rows_ == 1)
		res.matrix_[0][0] = 1.0 / matrix_[0][0];
	else {
		S21Matrix tmp = CalcComplements();
		res = tmp.Transpose();
		res.MulNumber(1 / determinant);
	}
	return res;
}

//------------------------------------------------------------------------------------------------------------------------
//OPERATORS
//------------------------------------------------------------------------------------------------------------------------

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
	if (!other.isValid())
        throw std::invalid_argument("Invalid matrix");
    if (this != &other) {
        S21Matrix tmp(other.rows_, other.cols_);
        for (int i = 0; i < tmp.rows_; i++) {
            for (int j = 0; j < tmp.cols_; j++) {
                tmp.matrix_[i][j] = other.matrix_[i][j];
            }
        }
        rows_ = tmp.rows_;
        cols_ = tmp.cols_;
        matrix_ = tmp.matrix_;
		tmp.matrix_ = nullptr;
	}
	return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
	SumMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
	this->SubMatrix(other);
	return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
	MulMatrix(other);
	return *this;
}

double& S21Matrix::operator()(int i, int j) {
	if (rows_ == 0 && cols_ == 0) {
		throw std::invalid_argument("Invalid argument");
	}
    if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
        throw std::invalid_argument("Invalid argument");
    return matrix_[i][j];
}

//------------------------------------------------------------------------------------------------------------------------
//GETTER AND SETTER
//------------------------------------------------------------------------------------------------------------------------

int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
void S21Matrix::setRows(const int rows) { this -> rows_ = rows; }
void S21Matrix::setCols(const int cols) { this -> cols_ = cols; }

//------------------------------------------------------------------------------------------------------------------------
//OPERATORS
//------------------------------------------------------------------------------------------------------------------------

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& rhs) {
	S21Matrix res = lhs;
	res += rhs;
	return res;
}

S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& rhs) {
	S21Matrix res = lhs;
	res -= rhs;
	return res;
}

S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& rhs) {
	S21Matrix res = lhs;
	res *= rhs;
	return res;
}

bool operator==(const S21Matrix& lhs, const S21Matrix& rhs) {
	return lhs.EqMatrix(rhs);
}