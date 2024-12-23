//Task 1

#include <iostream>
#include <memory>
#include <cstdlib>
#include <stdexcept>

class TMatrix {
private:
    int rows;
    int cols;
    std::unique_ptr<double[]> data;

public:
    TMatrix(int r, int c) : rows(r), cols(c) {
        data = std::make_unique<double[]>(rows * cols);
    }

    double& operator()(int r, int c) {
        return data[r * cols + c];
    }

    const double& operator()(int r, int c) const {
        return data[r * cols + c];
    }
    
    TMatrix add(const TMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("The matrices must have the same dimensions.");
        }

        TMatrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result;
    }

    TMatrix mult(const TMatrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("The number of columns of the first matrix must equal the number of rows of the second.");
        }

        TMatrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result(i, j) = 0;
                for (int k = 0; k < cols; ++k) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    static TMatrix OrphanRandomMatrix(int r, int c) {
        TMatrix randomMatrix(r, c);

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                randomMatrix(i, j) = static_cast<double>(std::rand() % 100);
            }
        }
        return randomMatrix;
    }

    double ComputeDeterminant() const {
        if (rows != cols) {
            throw std::invalid_argument("Only for a square matrix can the determinant be calculated.");
        }
        if (rows == 2) {
            return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
        }

        double determinant = 0.0;
        for (int col = 0; col < cols; ++col) {
            TMatrix minor(rows - 1, cols - 1);
            for (int i = 1; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (j < col) {
                        minor(i - 1, j) = (*this)(i, j);
                    } else if (j > col) {
                        minor(i - 1, j - 1) = (*this)(i, j);
                    }
                }
            }
            determinant += (col % 2 == 0 ? 1 : -1) * (*this)(0, col) * minor.ComputeDeterminant();
        }
        return determinant;
    }

    void printMatrix() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    TMatrix matrix1 = TMatrix::OrphanRandomMatrix(3, 3);
    TMatrix matrix2 = TMatrix::OrphanRandomMatrix(3, 3);

    std::cout << "Matrix 1:" << std::endl;
    matrix1.printMatrix();

    std::cout << "Matrix 2:" << std::endl;
    matrix2.printMatrix();

    TMatrix sum = matrix1.add(matrix2);
    std::cout << "Sum of matrices:" << std::endl;
    sum.printMatrix();

    TMatrix product = matrix1.mult(matrix2);
    std::cout << "Matrix product:" << std::endl;
    product.printMatrix();

    std::cout << "Determinant of a matrix 1: " << matrix1.ComputeDeterminant() << std::endl;
    std::cout << "Determinant of a matrix 2: " << matrix2.ComputeDeterminant() << std::endl;

    return 0;
}
