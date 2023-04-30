#include <iostream>

template <typename T>
class Rational {
private:
    T numerator;
    T denominator;

public:
    // Constructors
    Rational(T num = 0, T denom = 1) : numerator(num), denominator(denom) {
        simplify();
    }

    // Addition operator
    Rational<T> operator+(const Rational<T>& other) const {
        T num = numerator * other.denominator + other.numerator * denominator;
        T denom = denominator * other.denominator;
        return Rational<T>(num, denom);
    }

    // Subtraction operator
    Rational<T> operator-(const Rational<T>& other) const {
        T num = numerator * other.denominator - other.numerator * denominator;
        T denom = denominator * other.denominator;
        return Rational<T>(num, denom);
    }

    // Multiplication operator
    Rational<T> operator*(const Rational<T>& other) const {
        T num = numerator * other.numerator;
        T denom = denominator * other.denominator;
        return Rational<T>(num, denom);
    }

    // Division operator
    Rational<T> operator/(const Rational<T>& other) const {
        T num = numerator * other.denominator;
        T denom = denominator * other.numerator;
        return Rational<T>(num, denom);
    }

// Compound assignment: Subtraction
    Rational<T>& operator-=(const Rational<T>& other) {
        numerator = (numerator * other.denominator) - (other.numerator * denominator);
        denominator *= other.denominator;
        simplify();
        return *this;
    }

    // Compound assignment: Division
    Rational<T>& operator/=(const Rational<T>& other) {
        numerator *= other.denominator;
        denominator *= other.numerator;
        simplify();
        return *this;
    }


    // Left shift operator for the numerator and denominator
    Rational<T> shiftLeft(int shift) const {
        T shiftedNum = numerator << shift;
        T shiftedDenom = denominator << shift;
        return Rational<T>(shiftedNum, shiftedDenom);
    }

    // Right shift operator for the numerator and denominator
    Rational<T> shiftRight(int shift) const {
        T shiftedNum = numerator >> shift;
        T shiftedDenom = denominator >> shift;
        
        if (shiftedDenom == 0){
            return Rational<T>(0, 1);
        }

        return Rational<T>(shiftedNum, shiftedDenom);
    }

    bool operator>(const Rational<T>& other) const {
        // Multiply cross products to compare
        return (numerator * other.denominator) > (other.numerator * denominator);
    }


    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const Rational<T>& rational) {
        os << rational.numerator;
        if (rational.denominator != 1) {
            os << "/" << rational.denominator;
        }
        return os;
    }

    // Conversion to double type
    operator double() const {
        return static_cast<double>(numerator) / static_cast<double>(denominator);
    }

private:
    // Helper function to simplify the rational number
    void simplify() {
        if (numerator != 0) {
            T gcd = computeGCD(numerator, denominator);
            numerator /= gcd;
            denominator /= gcd;
        }
    }

    // Helper function to compute the greatest common divisor (GCD) using Euclid's algorithm
    T computeGCD(T a, T b) {
        bool bnot0 = 0;
        while (b != 0) {
            bnot0 = (b != 0);
            T temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Helper function to calculate the least common multiple
    int leastCommonMultiple(int a, int b) const {
        return (a / computeGCD(a, b)) * b;
    }

};