#include <iostream>
#include <vector>

template <typename T>
class Matrix {
private:
    
    size_t rows;
    size_t columns;

public:
    std::vector<std::vector<T>> elements;


    // Constructor
    Matrix(size_t numRows, size_t numColumns) : rows(numRows), columns(numColumns) {
        elements.resize(rows, std::vector<T>(columns));
    }

    // Addition operator
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || columns != other.columns) {
            throw std::runtime_error("Matrix dimensions do not match");
        }

        Matrix<T> result(rows, columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                result.elements[i][j] = elements[i][j] + other.elements[i][j];
            }
        }

        return result;
    }

    // Subtraction operator
    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || columns != other.columns) {
            throw std::runtime_error("Matrix dimensions do not match");
        }

        Matrix<T> result(rows, columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                result.elements[i][j] = elements[i][j] - other.elements[i][j];
            }
        }

        return result;
    }

    // Multiplication operator
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (columns != other.rows) {
            throw std::runtime_error("Matrix dimensions are incompatible for multiplication");
        }

        Matrix<T> result(rows, other.columns);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.columns; ++j) {
                for (size_t k = 0; k < columns; ++k) {
                    result.elements[i][j] += elements[i][k] * other.elements[k][j];
                }
            }
        }

        return result;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        for (const auto& row : matrix.elements) {
            for (const auto& element : row) {
                os << element << " ";
            }
            os << std::endl;
        }
        return os;
    }


    std::vector<T>& operator[](int index) {
        return elements[index];
    }

    const std::vector<T>& operator[](int index) const {
        return elements[index];
    }

    std::vector<T> solveEquations(const std::vector<T>& b) const {
        if (rows != columns || rows != b.size()) {
            throw std::invalid_argument("Matrix dimensions are not compatible for solving equations.");
        }

        // Augmented matrix [A|b]
        Matrix<T> augmentedMatrix(rows, columns + 1);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                augmentedMatrix[i][j] = elements[i][j];
            }
            augmentedMatrix[i][columns] = b[i];
        }

        // Forward elimination
        for (int i = 0; i < rows - 1; ++i) {
            // Find the pivot element
            int pivotRow = i;
            for (int j = i + 1; j < rows; ++j) {
                if (augmentedMatrix[j][i] > augmentedMatrix[pivotRow][i]) {
                    pivotRow = j;
                }
            }

            // Swap rows if necessary
            if (pivotRow != i) {
                std::swap(augmentedMatrix[i], augmentedMatrix[pivotRow]);
            }

            // Perform row operations to eliminate variables
            for (int j = i + 1; j < rows; ++j) {
                T ratio = augmentedMatrix[j][i] / augmentedMatrix[i][i];
                for (int k = i; k < columns + 1; ++k) {
                    augmentedMatrix[j][k] -= ratio * augmentedMatrix[i][k];
                }
            }
        }

        // Back substitution
        std::vector<T> solution(rows);
        for (int i = rows - 1; i >= 0; --i) {
            solution[i] = augmentedMatrix[i][columns];
            for (int j = i + 1; j < rows; ++j) {
                solution[i] -= augmentedMatrix[i][j] * solution[j];
            }
            solution[i] /= augmentedMatrix[i][i];
        }

        return solution;
    }
};

