#include <iostream>
#include <vector>

class LongInteger {
private:
    static const int BASE = 10000;  // Basis for representing digits (10^4)
    static const int WIDTH = 4;     // Width of each digit

    std::vector<int> digits;        // Vector to store the digits

public:
    // Constructor
    LongInteger(long long num = 0) {
        while (num > 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }

    // Addition operator
    LongInteger operator+(const LongInteger& other) const {
        LongInteger result;
        int carry = 0;
        int size = std::max(digits.size(), other.digits.size());

        for (int i = 0; i < size || carry; ++i) {
            if (i < digits.size())
                carry += digits[i];
            if (i < other.digits.size())
                carry += other.digits[i];

            result.digits.push_back(carry % BASE);
            carry /= BASE;
        }

        return result;
    }

    // Subtraction operator
    LongInteger operator-(const LongInteger& other) const {
        LongInteger result;
        int carry = 0;
        int size = digits.size();

        for (int i = 0; i < size; ++i) {
            int sub = digits[i] - carry;
            if (i < other.digits.size())
                sub -= other.digits[i];

            if (sub < 0) {
                sub += BASE;
                carry = 1;
            }
            else {
                carry = 0;
            }

            result.digits.push_back(sub);
        }

        while (result.digits.size() > 1 && result.digits.back() == 0)
            result.digits.pop_back();

        return result;
    }

    // Multiplication operator
    LongInteger operator*(const LongInteger& other) const {
        int size = digits.size() + other.digits.size();
        std::vector<int> resultDigits(size, 0);

        for (int i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; ++j) {
                long long cur = resultDigits[i + j] +
                    (i < digits.size() ? (long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0) : 0) +
                    carry;

                resultDigits[i + j] = cur % BASE;
                carry = cur / BASE;
            }
        }

        while (resultDigits.size() > 1 && resultDigits.back() == 0)
            resultDigits.pop_back();

        LongInteger result;
        result.digits = resultDigits;
        return result;
    }

    // Division operator
    LongInteger operator/(const LongInteger& other) const {
        if (other == 0)
            throw std::runtime_error("Division by zero");

        LongInteger dividend = *this;
        LongInteger divisor = other;
        LongInteger quotient;
        LongInteger remainder;

        for (int i = digits.size() - 1; i >= 0; --i) {
            remainder = remainder * BASE + digits[i];
            int q = binarySearch(divisor, remainder);

            quotient.digits.insert(quotient.digits.begin(), q);
            remainder = remainder - divisor * q;
        }

        while (quotient.digits.size() > 1 && quotient.digits.back() == 0)
            quotient.digits.pop_back();

        return quotient;
    }

    // Modulo operator
    LongInteger operator%(const LongInteger& other) const {
        LongInteger dividend = *this;
        LongInteger divisor = other;
        LongInteger quotient, remainder;

        // Normalize divisor to have the same number of digits as dividend
        int numZeroes = dividend.digits.size() - divisor.digits.size();
        for (int i = 0; i < numZeroes; ++i)
            divisor.digits.push_back(0);

        for (int i = dividend.digits.size() - 1; i >= 0; --i) {
            remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
            int q = 0;
            while (divisor <= remainder) {
                remainder -= divisor;
                ++q;
            }
            quotient.digits.insert(quotient.digits.begin(), q);
        }

        // Remove leading zeroes from remainder
        while (remainder.digits.size() > 1 && remainder.digits.back() == 0)
            remainder.digits.pop_back();

        if (remainder.digits[0] == 0){
            LongInteger zero(0);
            return zero;
        }

        return remainder;
    }

    // Left shift operator
    LongInteger operator<<(int shift) const {
        LongInteger result = *this;
        int shiftDigits = shift / WIDTH;
        int shiftRemainder = shift % WIDTH;

        // Shift the digits by shiftDigits
        for (int i = 0; i < shiftDigits; ++i) {
            result.digits.insert(result.digits.begin(), 0);
        }

        // Shift the individual digits within the last shifted digit
        int carry = 0;
        for (int i = result.digits.size() - 1; i >= 0; --i) {
            int newCarry = result.digits[i] / (BASE / 10);
            result.digits[i] = (result.digits[i] % (BASE / 10)) * (int)std::pow(10, shiftRemainder) + carry;
            carry = newCarry;
        }

        if (carry != 0) {
            result.digits.insert(result.digits.begin(), carry);
        }

        return result;
    }

    // Right shift operator
    LongInteger operator>>(int shift) const {
        LongInteger result = *this;
        int shiftDigits = shift / WIDTH;
        int shiftRemainder = shift % WIDTH;

        // Shift the digits by shiftDigits
        for (int i = 0; i < shiftDigits; ++i) {
            if (!result.digits.empty()) {
                result.digits.erase(result.digits.begin());
            }
        }

        // Shift the individual digits within the last shifted digit
        int carry = 0;
        for (int i = 0; i < result.digits.size(); ++i) {
            int newCarry = result.digits[i] % (int)std::pow(10, shiftRemainder);
            result.digits[i] = (result.digits[i] / (int)std::pow(10, shiftRemainder)) + carry * (BASE / 10);
            carry = newCarry;
        }

        return result;
    }



    // Addition assignment operator
    LongInteger& operator+=(const LongInteger& other) {
        *this = *this + other;
        return *this;
    }

    // Subtraction assignment operator
    LongInteger& operator-=(const LongInteger& other) {
        *this = *this - other;
        return *this;
    }

    // Multiplication assignment operator
    LongInteger& operator*=(const LongInteger& other) {
        *this = *this * other;
        return *this;
    }

    // Division assignment operator
    LongInteger& operator/=(const LongInteger& other) {
        *this = *this / other;
        return *this;
    }

    // Less than operator
    bool operator<(const LongInteger& other) const {
        if (digits.size() < other.digits.size())
            return true;
        if (digits.size() > other.digits.size())
            return false;

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] < other.digits[i])
                return true;
            if (digits[i] > other.digits[i])
                return false;
        }

        return false;
    }


    bool operator!=(const LongInteger& other) const {
        return !(*this == other);
    }

    bool operator!=(const int& other) const {
        LongInteger l_other(other);
        return !(*this == l_other);
    }

    bool operator==(const LongInteger& other) const {
        return digits == other.digits;
    }

    bool operator==(const int& other) const {
        LongInteger l_other(other);
        return (*this == l_other);
    }


    bool operator>(const LongInteger& other) const {
        if (this->digits.size() > other.digits.size()) {
            return true;
        }
        if (this->digits.size() < other.digits.size()) {
            return false;
        }

        // Compare digits from most significant to least significant
        for (int i = this->digits.size() - 1; i >= 0; --i) {
            if (this->digits[i] > other.digits[i]) {
                return true;
            }
            if (this->digits[i] < other.digits[i]) {
                return false;
            }
        }

        // Numbers are equal
        return false;
    }

    bool operator<=(const LongInteger& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return digits[i] < other.digits[i];
        }

        return true;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const LongInteger& num) {
        os << (num.digits.empty() ? 0 : num.digits.back());

        for (int i = num.digits.size() - 2; i >= 0; --i) {
            os.width(WIDTH);
            os.fill('0');
            os << num.digits[i];
        }

        return os;
    }

private:
    // Binary search to find the quotient digit
    int binarySearch(const LongInteger& divisor, const LongInteger& dividend) const {
        int left = 0;
        int right = BASE - 1;
        int result = 0;

        while (left <= right) {
            int mid = (left + right) / 2;
            LongInteger product = divisor * mid;

            if (product <= dividend) {
                result = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        return result;
    }
};
