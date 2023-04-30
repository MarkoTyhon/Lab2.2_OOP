#include <iostream>
#include <vector>

template <typename T>
class Vector {
private:
    size_t size;

public:
    std::vector<T> elements;


    // Constructor
    Vector(size_t n) : size(n) {
        elements.resize(size);
    }

    // Addition operator
    Vector<T> operator+(const Vector<T>& other) const {
        if (size != other.size) {
            throw std::runtime_error("Vector sizes do not match");
        }

        Vector<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            result.elements[i] = elements[i] + other.elements[i];
        }

        return result;
    }

    // Subtraction operator
    Vector<T> operator-(const Vector<T>& other) const {
        if (size != other.size) {
            throw std::runtime_error("Vector sizes do not match");
        }

        Vector<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            result.elements[i] = elements[i] - other.elements[i];
        }

        return result;
    }

    // Multiplication operator
    Vector<T> operator*(const Vector<T>& other) const {
        if (size != other.size) {
            throw std::runtime_error("Vector sizes do not match");
        }

        Vector<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            result.elements[i] = elements[i] * other.elements[i];
        }

        return result;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
        for (const auto& element : vec.elements) {
            os << element << " ";
        }
        return os;
    }
};
