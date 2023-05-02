#ifndef S21_MATRIX_OPP_H
#define S21_MATRIX_OPP_H

class S21Matrix {
    private:
        int rows_, cols_;
        double **matrix_;

    public:
        S21Matrix(); //  Конструктор
        ~S21Matrix(); // Деструктор
        S21Matrix(int rows, int cols);
        // S21Matrix(const S21Matrix& other);
        bool EqMatrix(const S21Matrix& other);
};

#endif