#include "LongInteger.cpp"
#include "Rational.cpp"
#include "Matrix.cpp"
#include "Vector.cpp"

#include <iostream>
#include <vector>

int main() {
    // Test with integer random matrix
    Matrix<LongInteger> randomMatrix(3, 3);
    randomMatrix[0] = { LongInteger(2), LongInteger(-1), LongInteger(1) };
    randomMatrix[1] = { LongInteger(1), LongInteger(3), LongInteger(-2) };
    randomMatrix[2] = { LongInteger(3), LongInteger(-1), LongInteger(4) };
    std::vector<LongInteger> bRandom = { LongInteger(3), LongInteger(1), LongInteger(5) };
    std::cout << "Random Matrix:\n" << randomMatrix << std::endl;
    std::cout << "Solution:\n";
    std::vector<LongInteger> solutionRandom = randomMatrix.solveEquations(bRandom);
    for (int i = 0; i < solutionRandom.size(); ++i) {
        std::cout << "x" << i + 1 << " = " << solutionRandom[i] << std::endl;
    }

    // Test with rational numbers using LongInteger as the base type
    Matrix<Rational<LongInteger>> rationalMatrix(3, 3);
    rationalMatrix[0] = { Rational<LongInteger>(2, 1), Rational<LongInteger>(-1, 1), Rational<LongInteger>(1, 1) };
    rationalMatrix[1] = { Rational<LongInteger>(1, 1), Rational<LongInteger>(3, 1), Rational<LongInteger>(-2, 1) };
    rationalMatrix[2] = { Rational<LongInteger>(3, 1), Rational<LongInteger>(-1, 1), Rational<LongInteger>(4, 1) };
    std::vector<Rational<LongInteger>> bRational = { Rational<LongInteger>(3, 1), Rational<LongInteger>(1, 1), Rational<LongInteger>(5, 1) };
    std::cout << "Rational Matrix:\n" << rationalMatrix << std::endl;
    std::cout << "Solution:\n";
    std::vector<Rational<LongInteger>> solutionRational = rationalMatrix.solveEquations(bRational);
    for (int i = 0; i < solutionRational.size(); ++i) {
        std::cout << "x" << i + 1 << " = " << solutionRational[i] << std::endl;
    }

    return 0;
}