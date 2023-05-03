#ifndef S21_MATRIX_OPP_H
#define S21_MATRIX_OPP_H

class S21Matrix {
    private:
        int rows_ = 0;
        int cols_ = 0;
        double **matrix_ = nullptr;
        bool isValidMatrix() const;
        S21Matrix getMatrixForMinor(int row, int col) const;

    public:
        S21Matrix(); // Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью
        S21Matrix(const int rows, const int cols); // Параметризированный конструктор с количеством строк и столбцов
        S21Matrix(const S21Matrix& other); // Конструктор копирования
        S21Matrix(S21Matrix&& other); // Конструктор переноса
        ~S21Matrix(); // Деструктор        

        S21Matrix &operator=(const S21Matrix& other);
        S21Matrix &operator+=(const S21Matrix& other);
        S21Matrix &operator-=(const S21Matrix& other);
        S21Matrix &operator*=(const double& other);
        S21Matrix &operator*=(const S21Matrix& other);

        double& operator()(int i, int j);

        bool EqMatrix(const S21Matrix& other) const; // Проверяет матрицы на равенство между собой
        void SumMatrix(const S21Matrix& other); // Прибавляет вторую матрицы к текущей
        void SubMatrix(const S21Matrix& other); // Вычитает из текущей матрицы другую
        void MulNumber(const double& other); // Умножает текущую матрицу на число
        void MulMatrix(const S21Matrix& other); // Умножает текущую матрицу на вторую
        S21Matrix Transpose() const; // Создает новую транспонированную матрицу из текущей и возвращает ее
        S21Matrix CalcComplements() const; // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
        double Determinant() const; // Вычисляет и возвращает определитель текущей матрицы
        S21Matrix InverseMatrix() const; // Вычисляет и возвращает обратную матрицу

        int GetRows() const;
        int GetCols() const;
        void SetRows(const int rows);
        void SetCols(const int cols);
        double det(double **a, int n) const;
        void new_pointer(double **a, double *b) const;
};

S21Matrix operator+(const S21Matrix& lhs, const S21Matrix& other);
S21Matrix operator-(const S21Matrix& lhs, const S21Matrix& other);
S21Matrix operator*(const S21Matrix& lhs, const S21Matrix& other);
S21Matrix operator*(const S21Matrix& lhs, const double& other);
S21Matrix operator*(const double& lhs, const S21Matrix& other);
bool operator==(const S21Matrix& lhs, const S21Matrix& other);

#endif